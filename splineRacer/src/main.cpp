#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <iostream>

#include "splineengine/common.hpp"
#include "splineengine/GameManager.hpp"
#include "splineengine/Settings.hpp"
#include <SDL/SDL_mixer.h>
// cmake ../splineRacer && make -j 4 && ./src/SPLINERACER


using namespace splineengine;


int main(int argc, char** argv) {
	// Initialize SDL and open a window
  glimac::SDLWindowManager windowManager(800, 600, "Spline Racer");

  // Initialize glew for OpenGL3+ support
  GLenum glewInitError = glewInit();
  if(GLEW_OK != glewInitError) {
      std::cerr << glewGetErrorString(glewInitError) << std::endl;
      return EXIT_FAILURE;
  }

  std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
  std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;

	if(Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1)
        std::cout << Mix_GetError() << std::endl;

  Mix_Music *music; //creation of musique
  music = Mix_LoadMUS("../splineRacer/assets/musics/instru_imac:.mp3");
  Mix_PlayMusic(music, -1);
	Mix_VolumeMusic(MIX_MAX_VOLUME);

  Settings& settings = Settings::instance();
	settings.appPath() = glimac::FilePath(argv[0]);
	GameManager& gameManager = GameManager::instance();

	try {
		gameManager.init();
	}
	catch(const Error &e) {
		// TODO : catch with a cool exception class
		e.what();
		return EXIT_FAILURE;
	}

	// Application loop:
	while(!gameManager.exiting()) {
		Uint32 startTime = SDL_GetTicks();

		// Event loop:
		SDL_Event e;
		while(windowManager.pollEvent(e)) {
			gameManager.handleEvent(e);
		}

		gameManager.update();
		settings.updateTime();

		windowManager.swapBuffers();

		//FPS regulator
		Uint32 elapsedTime = SDL_GetTicks() - startTime;
		if (elapsedTime < settings.framerate()) {
			//std::cout << "not lagging" << std::endl;
			SDL_Delay(settings.framerate() - elapsedTime);
		}
	}

	return EXIT_SUCCESS;
}
