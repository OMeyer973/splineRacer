#include <glimac/SDLWindowManager.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/Program.hpp>
#include <glimac/Geometry.hpp>
#include <splineengine/common.hpp>
#include <splineengine/Settings.hpp>
#include <splineengine/AssetManager.hpp>
#include <splineengine/Model.hpp>
#include <splineengine/GameObject.hpp>
#include <splineengine/TrackballCamera.hpp>
#include <splineengine/RenderManager.hpp>
#include <splineengine/POVCamera.hpp>
#include <splineengine/CubeMap.hpp>

// cmake ../splineRacer && make -j 4 && ./TP_splineTest/TP_splineTest_tinyObjLoaderTest

using namespace glimac;
using namespace splineengine;

void print(std::string str) {
	if (debug)
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
	AssetManager& assetManager = AssetManager::instance();
	Spline spline;

	glEnable(GL_DEPTH_TEST); // Permet d'activer le test de profondeur du GPU

	// Create the plane object
	GameObject player(assetManager.models()["plane"], spline);

	// Create a texture and load texture
	Texture planeTex("planetexture2.jpg");
	planeTex.loadTexture();

	// Create the skybox object
	GameObject skyboxObject(assetManager.models()["skybox"], spline);

	// Create the Cameras
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
							if (chosenCamera == TRACKBALL_CAMERA) {
								cameras[chosenCamera]->moveFront(zoom);
							}
							break;
						case SDLK_DOWN:
							if (chosenCamera == TRACKBALL_CAMERA) {
								cameras[chosenCamera]->moveFront(-zoom);
							}
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
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		renderManager.updateGlobalMatrix();

		/* Player */
		// Object transform
		player.sPosition() = glm::vec3(0);
		player.scale() = glm::vec3(1);
		// player.rotation() = glm::vec3(.25*cos(2*windowManager.getTime()), .25*cos(.5*windowManager.getTime()), 0);
		player.rotation() = glm::vec3(windowManager.getTime(), .5f*windowManager.getTime(), 0);

		// Update MVMatrix according to the object's transformation
		renderManager.updateMVMatrix(*cameras[chosenCamera], player.staticMatrix());
		renderManager.useProgram(DIRECTIONAL_LIGHT);

		// Texture binding
		glBindTexture(GL_TEXTURE_2D, planeTex.getTextureID());

		// Draw object
		player.draw();

		/* Skybox */
		// Object transform
		skyboxObject.scale() = 100.f*(fwdVec +upVec + leftVec); 

		// Update MVMatrix according to the object's transformation
		renderManager.updateMVMatrix(*cameras[chosenCamera], skyboxObject.staticMatrix());

		// Send uniforms to shaders
		renderManager.useProgram(TEXTURE);

		// Object drawing
		skyboxObject.draw();

		// Update the display
		windowManager.swapBuffers();
	}

	return EXIT_SUCCESS;
}
