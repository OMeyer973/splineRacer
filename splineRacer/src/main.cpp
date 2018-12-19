#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <iostream>

#include "splineengine/common.hpp"
#include "splineengine/GameManager.hpp"

// cmake ../splineRacer && make -j 4 && ./src/SPLINERACER


using namespace splineengine;

int main(int argc, char** argv) {

	std::cout << "main in " << std::endl;
	GameManager gameManager;

	try {
		gameManager.init();
	} 
	catch(...) {
		// TODO : catch with a cool exception class
		std::cerr << "GameManager initialisation error" << std::endl;
		return EXIT_FAILURE;
	}

	// Application loop:
	while(!gameManager.exiting()) {	
		gameManager.update();
	}

	return EXIT_SUCCESS;
}
