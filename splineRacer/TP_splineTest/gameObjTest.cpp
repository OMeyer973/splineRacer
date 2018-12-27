#include <iostream>
#include <GL/glew.h>
#include <glm/gtc/noise.hpp>

#include <glimac/SDLWindowManager.hpp>
#include <glimac/Program.hpp>
#include <glimac/common.hpp>
#include <glimac/Sphere.hpp>
#include <glimac/Geometry.hpp>

#include <splineengine/GameManager.hpp>
#include <splineengine/Settings.hpp>
#include <splineengine/RenderManager.hpp>
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
	
	Settings& settings = Settings::instance();
	settings.appPath() = glimac::FilePath(argv[0]);
	GameManager& gameManager = GameManager::instance();
	AssetManager& assetManager = AssetManager::instance();

	glimac::Sphere sphere(2, 3, 2);
	Spline spline;
	Player player(GameObject(
		assetManager.models()[PLANEMODEL], spline, false, 
		glm::vec3(0, 0, 5),
		glm::vec3(.5f, .5f, .5f),
		glm::vec3(0.0f, 0.0f, 0.f)
	));

	// Create a texture for the plane and load it
	Texture planeTex("planetexture2.jpg");
	planeTex.loadTexture();

	Texture singeTex("planetexture.jpg");
	singeTex.loadTexture();

	// Création des obstacles
	std::vector<GameObject> walls;

	for (float t=0; t<spline.length(); t+=.3f) {
		walls.push_back(GameObject(
			assetManager.models()[SINGEMODEL], spline, true,
			glm::vec3(t, 5*t, (int)t%10),
			glm::vec3(1.f, 1.f, 1.f),
			glm::vec3(0.0f, 0.0f, 0.f)
		));
	}

	// Charger et compiler les shaders
	// glimac::Program program = glimac::loadProgram(applicationPath.dirPath() + "shaders/3D.vs.glsl",
	//                             applicationPath.dirPath() + "shaders/normals.fs.glsl");
	// program.use(); // Indiquer a OpenGL de les utiliser

	// Create the Cameras
	std::vector<std::unique_ptr<Camera>> cameras; // Contains two pointers on camera
	cameras.emplace_back(new POVCamera());
	cameras.emplace_back(new TrackballCamera());
	int chosenCamera = TRACKBALL_CAMERA;

	// Init render manager
	RenderManager renderManager(*cameras[chosenCamera]);

	// 
	float cameraRotateSpeed = 0.4f;
	float zoom = 1.0f;

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

				// Camera handling
				if (e.key.keysym.sym==SDLK_c){
					chosenCamera = (chosenCamera == TRACKBALL_CAMERA) ? POV_CAMERA : TRACKBALL_CAMERA;
				}
				if (e.key.keysym.sym==SDLK_UP){
					if (chosenCamera == TRACKBALL_CAMERA) {
						cameras[chosenCamera]->moveFront(zoom);
					}
				}
				if (e.key.keysym.sym==SDLK_DOWN){
					if (chosenCamera == TRACKBALL_CAMERA) {
						cameras[chosenCamera]->moveFront(-zoom);
					}
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
				}
				break;
			case SDL_MOUSEMOTION:
				if (windowManager.isMouseButtonPressed(SDL_BUTTON_RIGHT)) {
					if (e.motion.xrel != 0) {
						cameras[chosenCamera]->rotateLeft(e.motion.xrel * cameraRotateSpeed);
					}
					if (e.motion.yrel != 0) {
						cameras[chosenCamera]->rotateUp(e.motion.yrel * cameraRotateSpeed);
					}
					break;
				}
			}
		}
		/*********************************
		 * RENDERING CODE
		 *********************************/
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		////////////////////////////////////////////////////////////
		// UPDATE

		gameManager.update();

		// to be put in a function in main architecture
		for (float i=0; i<walls.size(); ++i) {
			player.collideWith(walls[i]);
		}

		//updating player inner variables (speed, position...)
		if (!displayInGameMenu) {
			player.update(settings.deltaTime());
		}
		
		// END UPDATE
		////////////////////////////////////////////////////////////
		// RENDER

		glm::mat4 camMatrix = spline.camMatrix(player.sPosition());

		/////////////////////////////////////////
		// player render

		glm::mat4 MVMatrix;

		// get the transform matrix of the object
		MVMatrix = camMatrix * player.matrix();

		// Update MVMatrix according to the object's transformation
		renderManager.updateMVMatrix(*cameras[chosenCamera], MVMatrix);
		// Send uniforms to shaders
		renderManager.useProgram(NORMAL);
		renderManager.applyTransformations(NORMAL, renderManager.MVMatrix());

		// Texture binding
		glBindTexture(GL_TEXTURE_2D, planeTex.getTextureID());

		player.draw();

		glBindTexture(GL_TEXTURE_2D, 0);

		// End player render
		/////////////////////////////////////////
		// GameObjects render
		
		// Bind obstacle texture
		glBindTexture(GL_TEXTURE_2D, singeTex.getTextureID());

		for (float i=0; i<walls.size(); ++i) {
			glm::mat4 MVMatrix;

			// get the transform matrix of the object
			MVMatrix = camMatrix * walls[i].matrix();

			// Update MVMatrix according to the object's transformation
			renderManager.updateMVMatrix(*cameras[chosenCamera], MVMatrix);
			// Send uniforms to shaders
			renderManager.useProgram(DIRECTIONAL_LIGHT);
			renderManager.applyTransformations(DIRECTIONAL_LIGHT, renderManager.MVMatrix());

			walls[i].draw();
		}
		// Unbind obstacle texture
		glBindTexture(GL_TEXTURE_2D, 0);

		// End gameobj render
		////////////////////////////////

		// Update the display
		windowManager.swapBuffers();
		// FPS count
		Uint32 elapsedTime = SDL_GetTicks() - startTime;
		if(elapsedTime < FRAMERATE_MILLISECONDS) {
			//std::cout << "not lagging" << std::endl;
			SDL_Delay(FRAMERATE_MILLISECONDS - elapsedTime);
		}
	
		// END RENDER
		////////////////////////////////////////////////////////////////
	}

	return EXIT_SUCCESS;
}
