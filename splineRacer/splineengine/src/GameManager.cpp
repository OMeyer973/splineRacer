#include <splineengine/GameManager.hpp>

namespace splineengine {


GameManager::GameManager()
{}

void GameManager::init() {
	_menu.init();
	_pause.init();
}

// function just used in this file
// button can be SDL_BUTTON_LEFT, SDL_BUTTON_RIGHT and SDL_BUTTON_MIDDLE
bool isMouseButtonPressed(uint32_t button) {
    return SDL_GetMouseState(nullptr, nullptr) & SDL_BUTTON(button);
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
	            std::cout << "Space " << std::endl;
							goToGame();
	        }
	        if(e.key.keysym.sym==SDLK_z ) {
						if( !_menu.isRotatingHorizontally() && !_menu.isRotatingVertically() ){
							_menu.moveToLevel(1);
						}
	            //_levelId = (_levelId + 1) % NUMBER_OF_LEVELS;
	            //std::cout << "level id : " << _levelId << std::endl;
	        }
	        if(e.key.keysym.sym==SDLK_s  ) {
						if( !_menu.isRotatingHorizontally() && !_menu.isRotatingVertically() ){
							//_levelId = (_levelId - 1) % NUMBER_OF_LEVELS;
	            //std::cout << "level id : " << _levelId << std::endl;
							_menu.moveToLevel(-1);
						}

	        }
					if (e.key.keysym.sym==SDLK_q){ //going left
						if(!_menu.isRotatingHorizontally() ){
							_menu.moveToPannel(-1);
						}
				 }
				 if (e.key.keysym.sym==SDLK_d){//going right
					 if(!_menu.isRotatingHorizontally() ){
						_menu.moveToPannel(1);
					}
				 }
				 if(e.key.keysym.sym == SDLK_RETURN && _menu.getState() == "Play"){
					 _menu.setDisplayLevels();
				 }
				 // if(e.key.keysym.sym == SDLK_RETURN && _menu.getState()== "Play" && _menu.getDisplayLevels() ){
					//  goToGame();
				 // }
				 if(e.key.keysym.sym == SDLK_RETURN && _menu.getState() == "Quit"){
					_exiting = true;
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

			// Camera handling
			if (e.key.keysym.sym==SDLK_c){
				_game->changeCamera();
			}
			if (e.key.keysym.sym==SDLK_UP){
				_game->zoomCamera(cameraZoomSpeed);
			}
			if (e.key.keysym.sym==SDLK_DOWN){
				_game->zoomCamera(-cameraZoomSpeed);
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
		case SDL_MOUSEMOTION:
		 	if (isMouseButtonPressed(SDL_BUTTON_RIGHT)) {
		 		if (e.motion.xrel != 0) {
		 			_game->moveCameraX(e.motion.xrel);
				}
				if (e.motion.yrel != 0) {
					_game->moveCameraY(e.motion.yrel);
				}
				break;
			}
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
			if (_game->gameState() == EXITING) {
				goToMenu();
			}
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

	// TODO : add a parameter to loadLevel function in order to load a given level
	// (but keep loadLevel() without parameter to load the infinite level)
	if (_levelId == LEVEL_ENDLESS) {
		_game = std::unique_ptr<Game>(new Game());
		_game->loadLevel();
	} else {
		_game = std::unique_ptr<Game>(new Game(_levelId));
		_game->loadLevel(_levelId);
	}
}

void GameManager::goToGame() {
	std::cout << "going to game " << std::endl;
	//if no level has been initialized yet, load the infinite game
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

	//_menu.init();
}

}
