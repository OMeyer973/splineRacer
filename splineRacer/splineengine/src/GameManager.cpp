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
	if (e.type == SDL_QUIT)
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
	        if (input.up.has(e.key.keysym.sym)) {
				if (!_menu.isRotatingHorizontally() && !_menu.isRotatingVertically()){
					_menu.changeLevel(1);
				}
	        }
	        if (input.down.has(e.key.keysym.sym)) {
				if (!_menu.isRotatingHorizontally() && !_menu.isRotatingVertically()){
					_menu.changeLevel(-1);
				}
	        }
			if (input.left.has(e.key.keysym.sym)) { //going left
				if (!_menu.isRotatingHorizontally()) {
					_menu.changePannel(-1);
				}
			}
			if (input.right.has(e.key.keysym.sym)){//going right
				if (!_menu.isRotatingHorizontally()){
					_menu.changePannel(1);
				}
			}
			if (_menu.selectedMenu() == "Play") {
			 	
			 	if (_menu.isDisplayingLevels() && input.select.has(e.key.keysym.sym)) {
			 		_levelName = _menu.selectedLevel();
			 		goToGame();
			 	}
			 	if (input.select.has(e.key.keysym.sym)) {
					_menu.displayLevels();
				}
			 	if (input.back.has(e.key.keysym.sym)) {
					_menu.hideLevels();
			 	}
			
			}
			if (input.select.has(e.key.keysym.sym) && _menu.selectedMenu() == "Quit") {
				_exiting = true;
			}
	        break;
	}
}

void GameManager::doGameEvent(SDL_Event e) {
	switch (e.type) {
       case SDL_KEYDOWN:
	        if (input.left.has(e.key.keysym.sym)){ //going left
	            _game->player().goingLeft() = 1.f;
	        }
	        if (input.right.has(e.key.keysym.sym)){//going right
	            _game->player().goingLeft() = -1.f;
	        }
	         if (input.up.has(e.key.keysym.sym)){//going up
	            _game->player().goingUp() = 1.f;
	        }
	        if (input.down.has(e.key.keysym.sym)){//going down
	            _game->player().goingUp() = -1.f;
	        }
	        if (input.togglePause.has(e.key.keysym.sym)) {
				goToPause();
	        }
	        if (debug && e.key.keysym.sym==SDLK_SPACE) {
	            goToMenu();
	        }

			// Camera handling
			if (input.toggleCamera.has(e.key.keysym.sym)){
				_game->changeCamera();
			}
			if (input.cameraForward.has(e.key.keysym.sym)) {
				_game->zoomCamera(cameraZoomSpeed);
			}
			if (input.cameraBackward.has(e.key.keysym.sym)) {
				_game->zoomCamera(-cameraZoomSpeed);
			}
			break;

	    case SDL_KEYUP:
	        if (input.left.has(e.key.keysym.sym) && _game->player().goingLeft() > 0) {//stop going left
	            _game->player().goingLeft() = 0.f;
	        }
	        if (input.right.has(e.key.keysym.sym) && _game->player().goingLeft() < 0) {//stop going right
	            _game->player().goingLeft() = 0.f;
	        }
	        if (input.up.has(e.key.keysym.sym) && _game->player().goingUp() > 0) {//stop going up
	            _game->player().goingUp() = 0.f;
	        }
	        if (input.down.has(e.key.keysym.sym) && _game->player().goingUp() < 0){//stop going down
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
	        if (input.togglePause.has(e.key.keysym.sym)) {
				goToGame();
			}
	        if (debug && e.key.keysym.sym==SDLK_SPACE) {
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
	if (_levelName == "Endless") {
		_game = std::unique_ptr<Game>(new Game());
	} else {
		_game = std::unique_ptr<Game>(new Game(_levelName));
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
