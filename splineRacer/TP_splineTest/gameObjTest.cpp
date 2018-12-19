#include <iostream>
#include <GL/glew.h>
#include <glm/gtc/noise.hpp>

#include <glimac/SDLWindowManager.hpp>
#include <glimac/Program.hpp>
#include <glimac/common.hpp>
#include <glimac/Sphere.hpp>
#include <glimac/Geometry.hpp>

#include <splineengine/GameManager.hpp>
#include <splineengine/GameObject.hpp>
#include <splineengine/Player.hpp>
#include <splineengine/Spline.hpp>

//fps counter
#include <time.h>
//#include <GL/glut.h>
static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 30;


using namespace splineengine;

// cmake ../splineRacer && make -j 4 && ./TP_splineTest/TP_splineTest_gameObjTest



int initial_time = time(NULL), final_time, frame_count;

int main(int argc, char** argv) {
    // Initialize SDL and open a window
    glimac::SDLWindowManager windowManager(800, 600, "splineRacer");

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
    glimac::FilePath applicationPath(argv[0]);

    GameManager gameManager;
    glimac::Sphere sphere(2, 3, 2);
    Player player;
    Spline spline;

    Model planeModel(applicationPath, "plane");

    // Création d'un seul VBO = contient les données
    GLuint vbo;
    glGenBuffers(1, &vbo);

    //Binding d'un VBO sur la cible GL_ARRAY_BUFFER: permet de la modifier
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    //On peut à présent modifier le VBO en passant par la cible

    //Envoi des données
    glBufferData(GL_ARRAY_BUFFER, sphere.getVertexCount() * sizeof (glimac::ShapeVertex), sphere.getDataPointer(), GL_STATIC_DRAW);
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
    glVertexAttribPointer(VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof (glimac::ShapeVertex), (const GLvoid*) offsetof(glimac::ShapeVertex, position));
    glVertexAttribPointer(VERTEX_ATTR_NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof (glimac::ShapeVertex), (const GLvoid*) offsetof(glimac::ShapeVertex, normal));
    glVertexAttribPointer(VERTEX_ATTR_COORDINATE, 2, GL_FLOAT, GL_FALSE, sizeof (glimac::ShapeVertex), (const GLvoid*) offsetof(glimac::ShapeVertex, texCoords));

    //Débindage
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);



    // Charger et compiler les shaders
    glimac::Program program = glimac::loadProgram(applicationPath.dirPath() + "shaders/3D.vs.glsl",
                                applicationPath.dirPath() + "shaders/normals.fs.glsl");
    program.use(); // Indiquer a OpenGL de les utiliser



    glEnable(GL_DEPTH_TEST);
    bool displayInGameMenu = false;
    // Application loop:
    bool done = false;
    while(!done) {
        //set tickers to 0 for framerate cap
        Uint32 startTime = SDL_GetTicks();
        // Event loop:
        SDL_Event e;
        while(windowManager.pollEvent(e)) {
            switch (e.type) {
                case SDL_QUIT :
                    done = true; // Leave the loop after this iteration
                    break;
            case SDL_KEYDOWN:
                if (e.key.keysym.sym==SDLK_q){ //going left
                    player.goingLeft() = 1.f;
                }
                if (e.key.keysym.sym==SDLK_d){//going right
                    player.goingLeft() = -1.f;
                }
                 if (e.key.keysym.sym==SDLK_z){//going up
                    player.goingUp() = 1.f;
                }
                if (e.key.keysym.sym==SDLK_s){//going down
                    player.goingUp() = -1.f;
                }
                if(e.key.keysym.sym==SDLK_ESCAPE && !displayInGameMenu){
                    displayInGameMenu = true;
                }else if(e.key.keysym.sym == SDLK_ESCAPE && displayInGameMenu ){
                    displayInGameMenu = false;
                }

                break;

            case SDL_KEYUP:
                if (e.key.keysym.sym==SDLK_q && player.goingLeft() > 0) {//stop going left
                    player.goingLeft() = 0.f;
                }
                if (e.key.keysym.sym==SDLK_d && player.goingLeft() < 0) {//stop going right
                    player.goingLeft() = 0.f;
                }
                if (e.key.keysym.sym==SDLK_z && player.goingUp() > 0) {//stop going up
                    player.goingUp() = 0.f;
                }
                if (e.key.keysym.sym==SDLK_s && player.goingUp() < 0){//stop going down
                    player.goingUp() = 0.f;
                    ;
                }
                break;
            }
        }
        /*********************************
         * RENDERING CODE
         *********************************/
        gameManager.update();


        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        //calcul des view matrix, model matrix, projetion matrix
        glm::mat4 ProjMatrix = glm::perspective(glm::radians(110.f), 4.f/3.f, 0.1f, 100.f);


        //glm::mat4 MVMatrix = glm::translate(glm::mat4(), glm::vec3(0.f, 0.f ,-5.f));
        ///////////////
        // spline stuff

        //updating player inner variables (speed, position...)
        if (!displayInGameMenu)
            player.update(gameManager.deltaTime());


        glm::mat4 camMatrix = spline.camMatrix(player.sPosition());

        for (float t=1; t<100; t+=0.35f) {

            //curve part
            glm::mat4 MVMatrix;
            MVMatrix = camMatrix * spline.matrix(glm::vec3(t,0,0));
            //MVMatrix = glm::translate(camMatrix, spline.point(t));
            MVMatrix = glm::scale(MVMatrix, glm::vec3(0.2));

            for (int i=0; i<3; ++i) {
                if (i==1) {
                    MVMatrix = glm::translate(MVMatrix, glm::vec3(3,0,0));
                }
                if (i==2) {
                    MVMatrix = glm::translate(MVMatrix, glm::vec3(0,3,0));
                }
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
        }
        // end spline stuff
        ////////////////////////////////////////////////////////////////
        // gameobj stuff

        std::vector<GameObject> walls;

        for (float i=0; i<100; ++i) {
            walls.push_back (GameObject(
                /*planeModel,*/
                glm::vec3(3+i/8, 0.f, 1.5f),
                glm::vec3(0.4f, 0.4f, 0.4f),
                glm::vec3(0.0f, 0.0f, i/5)
            ));
        }

        for (float i=0; i<walls.size(); ++i) {
            glm::mat4 MVMatrix;

            // get the transform matrix of the object
            MVMatrix = camMatrix * walls[i].matrix(spline);

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
            //glBindVertexArray(vao);
            glBindVertexArray(planeModel.getVAO());
            glDrawElements(GL_TRIANGLES, planeModel.geometry().getIndexCount(), GL_UNSIGNED_INT, 0); // Draw all meshes
            //glDrawArrays(GL_TRIANGLES, 0, sphere.getVertexCount());

            glBindVertexArray(0);
        }

        //end gameobj stuff
        ////////////////////////////////////////////////////////////////
        // Update the display
        windowManager.swapBuffers();
        //fps count
        Uint32 elapsedTime = SDL_GetTicks() - startTime;
            if(elapsedTime < FRAMERATE_MILLISECONDS) {
                //std::cout << "not lagging" << std::endl;
                SDL_Delay(FRAMERATE_MILLISECONDS - elapsedTime);
            }



    }

    return EXIT_SUCCESS;
}
