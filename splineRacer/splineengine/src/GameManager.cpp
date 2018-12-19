#include <splineengine/GameManager.hpp>
#include <splineengine/Settings.hpp>

#include <memory>

namespace splineengine {


GameManager::GameManager()
{}

void GameManager::init() {
	_menu.init();
	_pause.init();
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
	switch (e.type) {
       case SDL_KEYDOWN:
	        if(e.key.keysym.sym==SDLK_SPACE) {
	            goToGame();
	        }
	        break;
	}
}

void GameManager::doGameEvent(SDL_Event e) {
	switch (e.type) {
       case SDL_KEYDOWN:
	        if (e.key.keysym.sym==SDLK_q){ //going left
	            _game->player().goingLeft() = 1.f;
	        }
	        if (e.key.keysym.sym==SDLK_d){//going right
	            _game->player().goingLeft() = -1.f;
	        }
	         if (e.key.keysym.sym==SDLK_z){//going up
	            _game->player().goingUp() = 1.f;
	        }
	        if (e.key.keysym.sym==SDLK_s){//going down
	            _game->player().goingUp() = -1.f;
	        }
	        if(e.key.keysym.sym==SDLK_ESCAPE) {
				goToPause();
	        }
	        if(e.key.keysym.sym==SDLK_SPACE) {
	            goToMenu();
	        }
	        break;

	    case SDL_KEYUP:
	        if (e.key.keysym.sym==SDLK_q && _game->player().goingLeft() > 0) {//stop going left
	            _game->player().goingLeft() = 0.f;
	        }
	        if (e.key.keysym.sym==SDLK_d && _game->player().goingLeft() < 0) {//stop going right
	            _game->player().goingLeft() = 0.f;
	        }
	        if (e.key.keysym.sym==SDLK_z && _game->player().goingUp() > 0) {//stop going up
	            _game->player().goingUp() = 0.f;
	        }
	        if (e.key.keysym.sym==SDLK_s && _game->player().goingUp() < 0){//stop going down
	            _game->player().goingUp() = 0.f;
	            ;
	        }
	        break;
    }
}


void GameManager::doPauseEvent(SDL_Event e) {
	// TODO
	switch (e.type) {
       case SDL_KEYDOWN:
	        if(e.key.keysym.sym==SDLK_ESCAPE) {
				goToGame();
			}
	        if(e.key.keysym.sym==SDLK_SPACE) {
				goToMenu();
			}
			break;
	}
}


void GameManager::update() {
	// note : events are handled before update
	// std::cout << "gamemanager update in " << std::endl;	
	switch (_activeScreen) {
	 	case MENU :
	 		_menu.update();
	 		_menu.render();
             break;
		case GAME :
			_game->update();
			_game->render();
            break;
	 	case PAUSE :
	 		_pause.update();
	 		_game->render();
	 		_pause.render();
             break;
	}
	// std::cout << "gamemanager update out " << std::endl;	
}

void GameManager::initGame() {
	std::cout << "initiating a game " << std::endl;
	if (_game != nullptr) {
		_game.reset();
	}
	_game = std::unique_ptr<Game>(new Game());
	
	// TODO : add a parameter to loadLevel function in order to load a given level
	// (but keep loadLevel() without parameter to load the infinite level)
	_game->loadLevel(/*_levelId*/);
}

void GameManager::goToGame() {
	std::cout << "going to game " << std::endl;
	if (_game == nullptr)
		initGame();

	_activeScreen = GAME;
}

void GameManager::goToPause() {
	std::cout << "going to pause " << std::endl;
	
	_pause.init();

	_activeScreen = PAUSE;
}

void GameManager::goToMenu() {
	std::cout << "going to menu " << std::endl;
	_game.reset();
	
	_activeScreen = MENU;

	_menu.init();
}

}