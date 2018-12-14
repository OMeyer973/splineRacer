#include <glimac/SDLWindowManager.hpp>
#include <glimac/Sphere.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/Program.hpp>
#include <glimac/Geometry.hpp>
#include <glimac/Image.hpp>
#include <glm/gtc/random.hpp>
#include <GL/glew.h>
#include <iostream>

using namespace glimac;

int main(int argc, char** argv) {
	// Initialize SDL and open a window
	SDLWindowManager windowManager(800, 600, "splineRacer");

	// Initialize glew for OpenGL3+ support
	GLenum glewInitError = glewInit();
	if(GLEW_OK != glewInitError) {
		std::cerr << glewGetErrorString(glewInitError) << std::endl;
		return EXIT_FAILURE;
	}

	std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
	std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;

	/*********************************
	 * HERE SHOULD COME THE INITIALIZATION CODE
	 *********************************/

	// Shaders
	FilePath applicationPath(argv[0]);
	Program program = loadProgram(applicationPath.dirPath() + "shaders/3D.vs.glsl",
								  applicationPath.dirPath() + "shaders/normals.fs.glsl");
	program.use();

	// Location des variables uniformes
	GLint MVPMatrixLocation = glGetUniformLocation(program.getGLId(), "uMVPMatrix");
	GLint MVMatrixLocation = glGetUniformLocation(program.getGLId(), "uMVMatrix");
	GLint NormalMatrixLocation = glGetUniformLocation(program.getGLId(), "uNormalMatrix");
	GLint textureLocation = glGetUniformLocation(program.getGLId(), "uTexture");
	
	glEnable(GL_DEPTH_TEST); // Permet d'activer le test de profondeur du GPU

	// Chargement d'une texture
	std::unique_ptr<Image> earthTexture = loadImage("/home/torresf/CLionProjects/splineRacer/splineRacer/assets/textures/EarthMap.jpg");

	if (earthTexture == NULL)
		std::cerr << "Erreur au chargement de l'image de la Terre." << std::endl;

	unsigned int nbTextures = 1;
	GLuint *textures = new GLuint[nbTextures];
	glGenTextures(nbTextures, textures);

	glBindTexture(GL_TEXTURE_2D, textures[0]);
	glTexImage2D(GL_TEXTURE_2D,
		0,
		GL_RGBA,
		earthTexture->getWidth(),
		earthTexture->getHeight(),
		0,
		GL_RGBA,
		GL_FLOAT,
		earthTexture->getPixels());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);

	glm::mat4 ProjMatrix = glm::perspective(glm::radians(70.f), 800 / 600.f, 0.1f, 100.f);
	glm::mat4 MVMatrix = glm::translate(glm::mat4(), glm::vec3(0, 0, -5));
	glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MVMatrix));

	Geometry plane;
	bool ret = plane.loadOBJ("/home/torresf/CLionProjects/splineRacer/splineRacer/assets/models/singe/singe.obj", 
							 "/home/torresf/CLionProjects/splineRacer/splineRacer/assets/models/singe/singe.mtl", 
							 true);

	if (!ret) {
		exit(1); // Lancer Exception
	}

	// Création d'une sphère
	Sphere sphere(1, 32, 16);

	GLuint vbo;
	glGenBuffers(1, &vbo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	// Envoie des données de vertex
	glBufferData(GL_ARRAY_BUFFER, plane.getVertexCount() * sizeof(Geometry::Vertex), plane.getVertexBuffer(), GL_STATIC_DRAW);
	
	// Débinding du VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//Gestion de l'ibo
	GLuint ibo;
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, plane.getIndexCount() * sizeof(uint32_t), plane.getIndexBuffer(), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// Création du VAO
	GLuint vao;
	glGenVertexArrays(1, &vao);

	// Binding du VAO
	glBindVertexArray(vao);

	// => On bind l'IBO sur GL_ELEMENT_ARRAY_BUFFER; puisqu'un VAO est actuellement bindé,
    // cela a pour effet d'enregistrer l'IBO dans le VAO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

	const GLuint VERTEX_ATTR_POSITION = 0;
	const GLuint VERTEX_ATTR_NORMAL = 1;
	const GLuint VERTEX_ATTR_TEXCOORD = 2;
	glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
	glEnableVertexAttribArray(VERTEX_ATTR_NORMAL);
	glEnableVertexAttribArray(VERTEX_ATTR_TEXCOORD);

	// Spécification de l'attribut de sommet et de texture
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(Geometry::Vertex), (const GLvoid*) offsetof(Geometry::Vertex, m_Position));
	glVertexAttribPointer(VERTEX_ATTR_NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(Geometry::Vertex), (const GLvoid*) offsetof(Geometry::Vertex, m_Normal));
	glVertexAttribPointer(VERTEX_ATTR_TEXCOORD, 2, GL_FLOAT, GL_FALSE, sizeof(Geometry::Vertex), (const GLvoid*) offsetof(Geometry::Vertex, m_TexCoords));
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Débinding du VAO
	glBindVertexArray(0);

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
		 * HERE SHOULD COME THE RENDERING CODE
		 *********************************/

		glBindTexture(GL_TEXTURE_2D, textures[0]);
		glUniform1i(textureLocation, 0);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		MVMatrix = glm::translate(glm::mat4(1), glm::vec3(0, 0, -5)); // Translation
		MVMatrix = glm::rotate(MVMatrix, windowManager.getTime(), glm::vec3(0, 1, 0)); // Translation * Rotation
		glUniformMatrix4fv(MVPMatrixLocation, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));
		glUniformMatrix4fv(MVMatrixLocation, 1, GL_FALSE, glm::value_ptr(MVMatrix));
		glUniformMatrix4fv(NormalMatrixLocation, 1, GL_FALSE, glm::value_ptr(NormalMatrix));

		// Dessin de la terre
		glBindVertexArray(vao);
		// => On utilise glDrawElements à la place de glDrawArrays
        // Cela indique à OpenGL qu'il doit utiliser l'IBO enregistré dans le VAO
        glDrawElements(GL_TRIANGLES, plane.getIndexCount(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		glBindTexture(GL_TEXTURE_2D, 0);

		// Update the display
		windowManager.swapBuffers();
	}

	// Libérations des ressources
	glDeleteBuffers(1, &vbo);
	glDeleteVertexArrays(1, &vao);
	delete textures;

	return EXIT_SUCCESS;
}
