#include <splineengine/GameManager.hpp>


namespace splineengine {


GameManager::GameManager()
	:_windowManager(_windowWidth, _windowHeight, "splineRacer")
	{}

GameManager::GameManager(glimac::SDLWindowManager windowManager)
	:_windowManager(windowManager)
	//segfault quand est appelé le constructeur de windowmanager...
	//j'avais un truc qui marchait tout à l'heure ouech
	//les prints ne sont même pas affichés à l'intérieur du constructeur de SDLWindowManager :'('
{
	std::cout << "GameManager constructor in" << std::endl;
}

void GameManager::init() {

    // Initialize glew for OpenGL3+ support
    GLenum glewInitError = glewInit();
    if(GLEW_OK != glewInitError) {
        std::cerr << glewGetErrorString(glewInitError) << std::endl;
    	// TODO : throw a cool exception with the exception class
        throw EXIT_FAILURE;
    }

    std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;
}


void GameManager::update() {

	handleEvents();

	// comment faire que le menu ou le game puisse dire au gameManager qu'il doit changer d'écran ? 
	// ex quand on lance une partie
	// le menu doit pouvoir accéder au gamemanager (qui est son parent)
	// solution : faire un singleton ! comme ça on peut accéder à gamemanager depuis partout et c'est cool
	// -> j'ai essayé de faire ça mais il était tard, j'ai eu des bugs relou et ça a pas marché.
	// 	https://h-deb.clg.qc.ca/Sujets/Divers--cplusplus/CPP--Singletons.html (methode 2)
	std::cout << "gamemanager update in " << std::endl;	
	// switch (_activeScreen) {
	// 	case MENU :
	// 		_menu.update();
	// 		_menu.render();
 //            break;
	// 	case GAME :
	// 		_game.update();
	// 		_game.render();
 //            break;
	// 	case PAUSE :
	// 		_pause.update();
	// 		_game.render();
	// 		_pause.render();
 //            break;
	// }
	std::cout << "gamemanager update out " << std::endl;	
	
	_windowManager.swapBuffers();
}


void GameManager::handleEvents() {
	// Event loop:
	SDL_Event e;
	while(_windowManager.pollEvent(e)) {
		if(e.type == SDL_QUIT)
			_exiting = true; // Leave the game loop after this iteration
		else {
			switch (_activeScreen) {
				case MENU :
                    doMenuEvent(e); 
                    break;
				case GAME :
                    doGameEvent(e); 
                    break;
				case PAUSE :
                    doPauseEvent(e); 
                    break;
			}
		}		
	}
}

void GameManager::doMenuEvent(SDL_Event e) {
	// TODO
}

void GameManager::doGameEvent(SDL_Event e) {
	// switch (e.type) {
 //       case SDL_KEYDOWN:
	//         if (e.key.keysym.sym==SDLK_q){ //going left
	//             _game.player().goingLeft() = 1.f;
	//         }
	//         if (e.key.keysym.sym==SDLK_d){//going right
	//             _game.player().goingLeft() = -1.f;
	//         }
	//          if (e.key.keysym.sym==SDLK_z){//going up
	//             _game.player().goingUp() = 1.f;
	//         }
	//         if (e.key.keysym.sym==SDLK_s){//going down
	//             _game.player().goingUp() = -1.f;
	//         }
	//         if(e.key.keysym.sym==SDLK_ESCAPE) {
	//             _activeScreen = PAUSE;
	//         }
	//         break;

	//     case SDL_KEYUP:
	//         if (e.key.keysym.sym==SDLK_q && _game.player().goingLeft() > 0) {//stop going left
	//             _game.player().goingLeft() = 0.f;
	//         }
	//         if (e.key.keysym.sym==SDLK_d && _game.player().goingLeft() < 0) {//stop going right
	//             _game.player().goingLeft() = 0.f;
	//         }
	//         if (e.key.keysym.sym==SDLK_z && _game.player().goingUp() > 0) {//stop going up
	//             _game.player().goingUp() = 0.f;
	//         }
	//         if (e.key.keysym.sym==SDLK_s && _game.player().goingUp() < 0){//stop going down
	//             _game.player().goingUp() = 0.f;
	//             ;
	//         }
	//         break;
	//     }
}


void GameManager::doPauseEvent(SDL_Event e) {
	// TODO
}



}