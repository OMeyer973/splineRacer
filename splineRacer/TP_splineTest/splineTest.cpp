#include <glimac/SDLWindowManager.hpp>
#include <glimac/Program.hpp>
#include <glimac/common.hpp>
#include <glimac/Sphere.hpp>
#include <GL/glew.h>
#include <iostream>

using namespace glimac;

// cmake ../splineRacer && make -j 4 && ./TP_splineTest/TP_splineTest_splineTest

Sphere sphere(1, 8, 4);


glm::vec3 spline(float t) {
    return glm::vec3(glm::sin(t), glm::cos(t), t);
}

int main(int argc, char** argv) {
    // Initialize SDL and open a window
    SDLWindowManager windowManager(800, 600, "GLImac");

    // Initialize glew for OpenGL3+ support
    GLenum glewInitError = glewInit();
    if(GLEW_OK != glewInitError) {
        std::cerr << glewGetErrorString(glewInitError) << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;

    /*********************************
     * INITIALIZATION CODE
     *********************************/
    
    // Création d'un seul VBO = contient les données
    GLuint vbo;
    glGenBuffers(1, &vbo);
    
    //Binding d'un VBO sur la cible GL_ARRAY_BUFFER: permet de la modifier
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    //On peut à présent modifier le VBO en passant par la cible 

    //Envoi des données
    glBufferData(GL_ARRAY_BUFFER, sphere.getVertexCount() * sizeof (ShapeVertex), sphere.getDataPointer(), GL_STATIC_DRAW);
    //On utilise GL_STATIC_DRAW pour un buffer dont les données ne changeront jamais.

    //Débindage, pour éviter de remodifier le VBO par erreur.
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    //Création du VAO (Vertex Array Object) = décrit les données dans le VBOs
    GLuint vao;
    glGenVertexArrays(1, &vao);

    //Binding du VAO
    glBindVertexArray(vao);

    //Activation des attributs de vertex
    const GLuint VERTEX_ATTR_POSITION = 0;
    const GLuint VERTEX_ATTR_NORMAL = 1;
    const GLuint VERTEX_ATTR_COORDINATE = 2;
    glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
    glEnableVertexAttribArray(VERTEX_ATTR_NORMAL);
    glEnableVertexAttribArray(VERTEX_ATTR_COORDINATE);

    //Binding d'un VBO sur la cible GL_ARRAY_BUFFER:
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    //Spécification des attributs de vertex
    //glVertexAttribPointer(GLuint index,GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid* pointer);
    glVertexAttribPointer(VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof (ShapeVertex), (const GLvoid*) offsetof(ShapeVertex, position));
    glVertexAttribPointer(VERTEX_ATTR_NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof (ShapeVertex), (const GLvoid*) offsetof(ShapeVertex, normal));
    glVertexAttribPointer(VERTEX_ATTR_COORDINATE, 2, GL_FLOAT, GL_FALSE, sizeof (ShapeVertex), (const GLvoid*) offsetof(ShapeVertex, texCoords));

    //Débindage
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);



    // Charger et compiler les shaders
    FilePath applicationPath(argv[0]);
    Program program = loadProgram(applicationPath.dirPath() + "shaders/3D.vs.glsl",
                                applicationPath.dirPath() + "shaders/normals.fs.glsl");
    program.use(); // Indiquer a OpenGL de les utiliser

    glEnable(GL_DEPTH_TEST);

    // Application loop:
    bool done = false;
    while(!done) {
        // Event loop:
        SDL_Event e;
        while(windowManager.pollEvent(e)) {
            if(e.type == SDL_QUIT) {
                done = true; // Leave the loop after this iteration
            }
        }
        /*********************************
         * RENDERING CODE
         *********************************/
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        
        //calcul des view matrix, model matrix, projetion matrix
        glm::mat4 ProjMatrix = glm::perspective(glm::radians(90.f), 4.f/3.f, 0.1f, 100.f);
        

        //glm::mat4 MVMatrix = glm::translate(glm::mat4(), glm::vec3(0.f, 0.f ,-5.f));
        ///////////////////////////////////////////////////////////////////////
        // spline stuff

        glm::mat4 camMatrix = glm::mat4();    
        //camera part
        //camMatrix = glm::translate(camMatrix, glm::vec3(0.2,0.2,0));
        //how far have we traveled on the pline ?
        float camProgress = windowManager.getTime();
        float delta = 0.1;

        //translation of the camera folowing the spline (here the camera is inside the spline)
        glm::vec3 camPos = spline(camProgress);
        //camPos.x *= 0.7; 
        //camPos.y *= 0.7; 

        camMatrix = glm::translate(camMatrix, camPos);
        
        //calculating the 3 vectors of the spline reference
        glm::vec3 zS = glm::normalize(spline(camProgress+delta) - spline(camProgress-delta));
        glm::vec3 yS = glm::normalize(glm::cross(glm::vec3(0,1,0), zS));
        glm::vec3 xS = glm::normalize(glm::cross(zS, yS));

        float splineRotContent[16] = {
            xS[0], yS[0], zS[0], 0,
            xS[1], yS[1], zS[1], 0,
            xS[2], yS[2], zS[2], 0,
            0    , 0    , 0    , 1};

        glm::mat4 splineRotMat = glm::make_mat4(splineRotContent);

        camMatrix = splineRotMat * camMatrix;
        //here the camera is inside the spline

        // TODO : here should come the rotation around the curve part 
        // but I can't find the right axis
        // or maybe it's not here that this should be done
        // idk anymore
        //camMatrix = glm::rotate(camMatrix, 3*windowManager.getTime(), zS);

        //offset to hover above the spline
        camMatrix = glm::translate(camMatrix, glm::vec3(-0.6,0,0));


        for (float t=3; t<50; t+=0.2) {

            //curve part
            glm::mat4 MVMatrix = glm::translate(camMatrix, -spline(t));
            MVMatrix = glm::scale(MVMatrix, glm::vec3(0.2));
            
            // end spline stuff
            ////////////////////////////////////////////////////////////////  
            glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MVMatrix));

            //on récupère les locations des variables uniformes dans les shaders
            GLint uMVPMatrixLocation = glGetUniformLocation(program.getGLId(), "uMVPMatrix");
            GLint uMVMatrix = glGetUniformLocation(program.getGLId(), "uMVMatrix");
            GLint uNormalMatrix = glGetUniformLocation(program.getGLId(), "uNormalMatrix");
            //on envoie les matrices à la CG dans les variables uniformes
            glUniformMatrix4fv(uMVPMatrixLocation, 1, GL_FALSE,  glm::value_ptr(ProjMatrix * MVMatrix));
            glUniformMatrix4fv(uMVMatrix, 1, GL_FALSE,  glm::value_ptr(MVMatrix));
            glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE,  glm::value_ptr(NormalMatrix));

            //Binding du VAO
            glBindVertexArray(vao);

            glDrawArrays(GL_TRIANGLES, 0, sphere.getVertexCount());

            glBindVertexArray(0);

        }
        // Update the display
        windowManager.swapBuffers();
    }

    return EXIT_SUCCESS;
}
