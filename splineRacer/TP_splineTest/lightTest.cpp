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
#include <splineengine/GameObject.hpp>
#include <splineengine/Model.hpp>
#include <splineengine/POVCamera.hpp>
#include <splineengine/TrackballCamera.hpp>
#include <splineengine/RenderManager.hpp>
#include <splineengine/Settings.hpp>
#include <splineengine/common.hpp>
#include <splineengine/CubeMap.hpp>

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
	Settings& settings = Settings::instance();
	settings.appPath() = glimac::FilePath(argv[0]);

	// Shaders
	FilePath applicationPath(argv[0]);
	Program program = loadProgram(applicationPath.dirPath() + "shaders/3D.vs.glsl",
								  applicationPath.dirPath() + "shaders/directionalLight.fs.glsl");
	program.use();

	GLint uLightIntensity = glGetUniformLocation(program.getGLId(), "uLightIntensity");
	GLint uLightDir_vs = glGetUniformLocation(program.getGLId(), "uLightDir_vs");
	GLint uKd = glGetUniformLocation(program.getGLId(), "uKd");
	GLint uKs = glGetUniformLocation(program.getGLId(), "uKs");
	GLint uKa = glGetUniformLocation(program.getGLId(), "uKa");
	GLint uShininess = glGetUniformLocation(program.getGLId(), "uShininess");

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

	Spline spline;

	// Create the model and create VBO, IBO, VAO based on the geometry
	Model planeModel("plane");
	GameObject planeObject(planeModel, spline);

	// Create the Camera
	std::vector<std::unique_ptr<Camera>> cameras; // Contains two pointers on camera
	cameras.emplace_back(new POVCamera());
	cameras.emplace_back(new TrackballCamera());
	int chosenCamera = TRACKBALL_CAMERA;

	RenderManager renderManager(*cameras[chosenCamera]);

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

		program.use();

		planeObject.scale() = glm::vec3(1);
		planeObject.sPosition() = glm::vec3(0);
		planeObject.rotation() = glm::vec3(.25*cos(2*windowManager.getTime()), .25*cos(.5*windowManager.getTime()), 0);

		renderManager.updateMVMatrix(*cameras[chosenCamera], planeObject.matrix());

		// Gestion de la lumière
		glm::mat4 globalMVMatrix = renderManager.MVMatrix();
		glm::mat4 lightMVMatrix = globalMVMatrix; // Translation * Rotation
		lightMVMatrix = glm::rotate(globalMVMatrix, windowManager.getTime(), glm::vec3(0, 1, 0)); // Translation * Rotation
		glm::vec3 lightDir_vs(lightMVMatrix * glm::vec4(1, 1, 1, 0));

		glUniform3f(uLightIntensity, 1, 1, 1);
		glUniform3fv(uLightDir_vs, 1, glm::value_ptr(lightDir_vs));
		glUniform3f(uKd, .5, .5, .5);
		glUniform3f(uKs, .5, .5, .5);
		glUniform3f(uKa, .1, .1, .1);
		glUniform1f(uShininess, 1);

		lightMVMatrix = globalMVMatrix;

		glUniformMatrix4fv(MVMatrixLocation, 1, GL_FALSE, glm::value_ptr(lightMVMatrix));
		glUniformMatrix4fv(NormalMatrixLocation, 1, GL_FALSE, glm::value_ptr(glm::transpose(glm::inverse(lightMVMatrix))));
		glUniformMatrix4fv(MVPMatrixLocation, 1, GL_FALSE, glm::value_ptr(renderManager.projMatrix() * lightMVMatrix));
		//FIN LUMIERE

		glBindTexture(GL_TEXTURE_2D, textures[0]);
		glUniform1i(textureLocation, 0);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// glUniformMatrix4fv(MVPMatrixLocation, 1, GL_FALSE, glm::value_ptr(renderManager.projMatrix() * renderManager.MVMatrix()));
		// glUniformMatrix4fv(MVMatrixLocation, 1, GL_FALSE, glm::value_ptr(renderManager.MVMatrix()));
		// glUniformMatrix4fv(NormalMatrixLocation, 1, GL_FALSE, glm::value_ptr(renderManager.normalMatrix()));

		planeObject.draw();

		glBindTexture(GL_TEXTURE_2D, 0);

		// Update the display
		windowManager.swapBuffers();
	}

	// Libérations des ressources
	delete textures;

	return EXIT_SUCCESS;
}
