#include <glm/gtc/random.hpp>
#include <GL/glew.h>
#include <iostream>
#include <vector>
#include <glimac/SDLWindowManager.hpp>
#include <glimac/Sphere.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/Program.hpp>
#include <glimac/Geometry.hpp>
#include <glimac/Image.hpp>
#include <splineengine/Model.hpp>
#include <splineengine/POVCamera.hpp>
#include <splineengine/TrackballCamera.hpp>


using namespace glimac;
using namespace splineengine;

void print(std::string str) {
	std::cout << "Debug : "<< str << std::endl;
}

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
								  applicationPath.dirPath() + "shaders/tex3D.fs.glsl");
	program.use();

	// Location des variables uniformes
	GLint MVPMatrixLocation = glGetUniformLocation(program.getGLId(), "uMVPMatrix");
	GLint MVMatrixLocation = glGetUniformLocation(program.getGLId(), "uMVMatrix");
	GLint NormalMatrixLocation = glGetUniformLocation(program.getGLId(), "uNormalMatrix");
	GLint textureLocation = glGetUniformLocation(program.getGLId(), "uTexture");

	glEnable(GL_DEPTH_TEST); // Permet d'activer le test de profondeur du GPU

	// Chargement d'une texture
	std::unique_ptr<Image> planeTexture = loadImage(applicationPath.dirPath() + "../../splineRacer/assets/textures/planetexture2.jpg");
	std::unique_ptr<Image> propellerTexture = loadImage(applicationPath.dirPath() + "../../splineRacer/assets/textures/finish_line2.jpg");

	if (planeTexture == NULL)
		std::cerr << "Erreur au chargement de l'image." << std::endl;

	unsigned int nbTextures = 2;
	GLuint *textures = new GLuint[nbTextures];
	glGenTextures(nbTextures, textures);

	glBindTexture(GL_TEXTURE_2D, textures[0]);
	glTexImage2D(GL_TEXTURE_2D,
		0,
		GL_RGBA,
		planeTexture->getWidth(),
		planeTexture->getHeight(),
		0,
		GL_RGBA,
		GL_FLOAT,
		planeTexture->getPixels());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);

	if (propellerTexture == NULL)
		std::cerr << "Erreur au chargement de l'image." << std::endl;

	glBindTexture(GL_TEXTURE_2D, textures[1]);
	glTexImage2D(GL_TEXTURE_2D,
		0,
		GL_RGBA,
		propellerTexture->getWidth(),
		propellerTexture->getHeight(),
		0,
		GL_RGBA,
		GL_FLOAT,
		propellerTexture->getPixels());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);

	glm::mat4 ProjMatrix = glm::perspective(glm::radians(70.f), 800 / 600.f, 0.1f, 100.f);
	glm::mat4 MVMatrix = glm::translate(glm::mat4(), glm::vec3(0, 0, -5));
	glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MVMatrix));

	// Create the model and create VBO, IBO, VAO based on the geometry
	Model planeModel(applicationPath, "plane");

	// Create the Camera
	std::vector<std::unique_ptr<Camera>> cameras;
	POVCamera povCamera;
	TrackballCamera tbCamera;
	cameras.emplace_back(new POVCamera());
	cameras.emplace_back(new TrackballCamera());
	int chosenCamera = POV_CAMERA;

	float rotateSpeed = 1.0f;
	float zoom = 1.0f;

	// Application loop:
	bool done = false;
	while(!done) {
		// Event loop:
		SDL_Event e;
		while(windowManager.pollEvent(e)) {
			switch (e.type) {
				case SDL_QUIT:
					done = true;
					break;
				case SDL_KEYDOWN:
					switch (e.key.keysym.sym) {
						case SDLK_ESCAPE:
							done = true;
							break;
						case SDLK_c:
							chosenCamera = (chosenCamera == TRACKBALL_CAMERA) ? POV_CAMERA : TRACKBALL_CAMERA;
							break;
						case SDLK_UP:
							if (chosenCamera == TRACKBALL_CAMERA)
								cameras[chosenCamera]->moveFront(zoom);
							break;
						case SDLK_DOWN:
							if (chosenCamera == TRACKBALL_CAMERA)
								cameras[chosenCamera]->moveFront(-zoom);
							break;
						default:
							break;
					}
					break;
				case SDL_MOUSEMOTION:
					if (windowManager.isMouseButtonPressed(SDL_BUTTON_RIGHT)) {
						if (e.motion.xrel != 0) {
							cameras[chosenCamera]->rotateLeft(e.motion.xrel * rotateSpeed);
						}
						if (e.motion.yrel != 0) {
							cameras[chosenCamera]->rotateUp(e.motion.yrel * rotateSpeed);
						}
						break;
					}
				default:
					break;
			}
		}

		/*********************************
		 * HERE SHOULD COME THE RENDERING CODE
		 *********************************/

		glBindTexture(GL_TEXTURE_2D, textures[0]);
		glUniform1i(textureLocation, 0);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		MVMatrix = cameras[chosenCamera]->getViewMatrix(); // Init MVMatrix based on the camera

		// MVMatrix = glm::translate(MVMatrix, glm::vec3(0, 0, -5)); // Translation
		// MVMatrix = glm::rotate(MVMatrix, windowManager.getTime(), glm::vec3(0, 1, 0)); // Translation * Rotation
		glUniformMatrix4fv(MVPMatrixLocation, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));
		glUniformMatrix4fv(MVMatrixLocation, 1, GL_FALSE, glm::value_ptr(MVMatrix));
		glUniformMatrix4fv(NormalMatrixLocation, 1, GL_FALSE, glm::value_ptr(NormalMatrix));

		// Dessin de l'OBJ
		glBindVertexArray(planeModel.getVAO());

		/* On boucle sur les meshs de l'object pour les afficher un par un et
		   appliquer des textures ou des tranformations différentes pour chaque mesh. */
		for (int i = 0; i < planeModel.geometry().getMeshCount(); ++i)
		{
			const Geometry::Mesh* currentMesh = (planeModel.geometry().getMeshBuffer()+i);
			GLint indexCount = currentMesh->m_nIndexCount;
			GLint indexOffset = currentMesh->m_nIndexOffset;
			if (currentMesh->m_sName == "propeller") // Si le mesh courant correspond aux hélices
			{
				glBindTexture(GL_TEXTURE_2D, textures[1]);
				glUniform1i(textureLocation, 0);
				MVMatrix = cameras[chosenCamera]->getViewMatrix(); // Init MVMatrix based on the camera
				// MVMatrix = glm::translate(MVMatrix, glm::vec3(0, 0, -5)); // Translation
				// MVMatrix = glm::rotate(MVMatrix, windowManager.getTime(), glm::vec3(0, 1, 0)); // Translation * Rotation
				MVMatrix = glm::rotate(MVMatrix, 10*windowManager.getTime(), glm::vec3(0, 0, 1)); // Translation * Rotation
				glUniformMatrix4fv(MVPMatrixLocation, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));
				glUniformMatrix4fv(MVMatrixLocation, 1, GL_FALSE, glm::value_ptr(MVMatrix));
				glUniformMatrix4fv(NormalMatrixLocation, 1, GL_FALSE, glm::value_ptr(NormalMatrix));
			}

			// => On utilise glDrawElements à la place de glDrawArrays
			// Cela indique à OpenGL qu'il doit utiliser l'IBO enregistré dans le VAO
			glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, (const GLvoid*) (indexOffset * sizeof(GLuint)));
		}
		// glDrawElements(GL_TRIANGLES, planeModel.geometry().getIndexCount(), GL_UNSIGNED_INT, 0); // Draw all meshes
		glBindVertexArray(0);
		glBindTexture(GL_TEXTURE_2D, 0);

		// Update the display
		windowManager.swapBuffers();
	}

	// Libérations des ressources
	delete textures;

	return EXIT_SUCCESS;
}
