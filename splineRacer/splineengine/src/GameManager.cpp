#include <splineengine/GameManager.hpp>


namespace splineengine {


GameManager::GameManager()
	:_game()
	{}

void GameManager::init() {
}


void GameManager::update() {

	// comment faire que le menu ou le game puisse dire au gameManager qu'il doit changer d'écran ? 
	// ex quand on lance une partie
	// le menu doit pouvoir accéder au gamemanager (qui est son parent)
	// solution : faire un singleton ! comme ça on peut accéder à gamemanager depuis partout et c'est cool
	// -> j'ai essayé de faire ça mais il était tard, j'ai eu des bugs relou et ça a pas marché.
	// 	https://h-deb.clg.qc.ca/Sujets/Divers--cplusplus/CPP--Singletons.html (methode 2)
	
	// std::cout << "gamemanager update in " << std::endl;	
	switch (_activeScreen) {
	 	case MENU :
	 		_menu.update();
	 		_menu.render();
             break;
		case GAME :
			_game.update();
			_game.render();
            break;
	 	case PAUSE :
	 		_pause.update();
	 		_game.render();
	 		_pause.render();
             break;
	}
	// std::cout << "gamemanager update out " << std::endl;	
}


void GameManager::handleEvent(SDL_Event e) {
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

void GameManager::doMenuEvent(SDL_Event e) {
	// TODO
}

void GameManager::doGameEvent(SDL_Event e) {
	switch (e.type) {
       case SDL_KEYDOWN:
	        if (e.key.keysym.sym==SDLK_q){ //going left
	            _game.player().goingLeft() = 1.f;
	        }
	        if (e.key.keysym.sym==SDLK_d){//going right
	            _game.player().goingLeft() = -1.f;
	        }
	         if (e.key.keysym.sym==SDLK_z){//going up
	            _game.player().goingUp() = 1.f;
	        }
	        if (e.key.keysym.sym==SDLK_s){//going down
	            _game.player().goingUp() = -1.f;
	        }
	        if(e.key.keysym.sym==SDLK_ESCAPE) {
	            _activeScreen = PAUSE;
	        }
	        break;

	    case SDL_KEYUP:
	        if (e.key.keysym.sym==SDLK_q && _game.player().goingLeft() > 0) {//stop going left
	            _game.player().goingLeft() = 0.f;
	        }
	        if (e.key.keysym.sym==SDLK_d && _game.player().goingLeft() < 0) {//stop going right
	            _game.player().goingLeft() = 0.f;
	        }
	        if (e.key.keysym.sym==SDLK_z && _game.player().goingUp() > 0) {//stop going up
	            _game.player().goingUp() = 0.f;
	        }
	        if (e.key.keysym.sym==SDLK_s && _game.player().goingUp() < 0){//stop going down
	            _game.player().goingUp() = 0.f;
	            ;
	        }
	        break;
	    }
}


void GameManager::doPauseEvent(SDL_Event e) {
	// TODO
}



}