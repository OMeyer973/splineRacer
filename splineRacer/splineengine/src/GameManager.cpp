#include <splineengine/GameManager.hpp>

namespace splineengine {


GameManager::GameManager()
{}

void GameManager::init() {
	if (_menu.init() != 0 || _pause.init() != 0)
	{
		throw Error("GameManager initialisation error", __FILE__, __LINE__);
	}
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
			if (input.select.has(e.key.keysym.sym) && _menu.selectedMenu() == "Quit") {
				_exiting = true;
			}
			if (_menu.selectedMenu() == "Play") {
			 	if (_menu.isDisplayingLevels()) {
				 	if (input.back.has(e.key.keysym.sym)) {
						_menu.hideLevels();
				 	}
			 		if (input.select.has(e.key.keysym.sym)) {
				 		_levelName = _menu.selectedLevel();
				 		goToGame(); // warning after this call, not in menu anymore
				 		break;
				 	}
			 	}
			 	if (input.select.has(e.key.keysym.sym)) {
					_menu.displayLevels();
				}
			}
      break;
		case SDL_JOYHATMOTION:
			if (e.jhat.hat == 0){
					switch(e.jhat.value)
					{
						case SDL_HAT_UP:
							if (!_menu.isRotatingHorizontally() && !_menu.isRotatingVertically()){
								_menu.changeLevel(1);
							}
							if(debug) std::cout << "UP"<< std::endl;
							break;
						case SDL_HAT_DOWN:
							if (!_menu.isRotatingHorizontally() && !_menu.isRotatingVertically()){
								_menu.changeLevel(-1);
							}
							if(debug) std::cout << "DOWN"<< std::endl;
							break;
						case SDL_HAT_LEFT:
							if (!_menu.isRotatingHorizontally()) {
								_menu.changePannel(-1);
							}
							if(debug) std::cout << "LEFT"<< std::endl;
							break;
						case SDL_HAT_RIGHT:
							if (!_menu.isRotatingHorizontally()){
								_menu.changePannel(1);
							}
							if(debug) std::cout << "RIGHT"<< std::endl;
							break;
						default:
							break;
					}
			}
			break;
		case SDL_JOYBUTTONDOWN:
			switch(e.jbutton.button){
				case 0 :	// ENTER
					if(debug) std::cout <<"A" << std::endl;
					if (_menu.selectedMenu() == "Play") {
						if (_menu.isDisplayingLevels()) {
							_levelName = _menu.selectedLevel();
							goToGame(); // warning after this call, not in menu anymore
							break;
						}else{
							_menu.displayLevels();
						}
					}
					break;
				case 1 :	// HIDE MENU
					if(_menu.isDisplayingLevels()){
						_menu.hideLevels();
						break;
					}
					if(debug) std::cout <<"B" << std::endl;
					break;
				case 2 :	// CAMERA SWITCH
					if(debug) std::cout <<"X"<< std::endl;
					break;
				case 3 :	// PAUSE
					if(debug) std::cout <<"Y" << std::endl;
					break;
				case 7 :	// INFOS
					if(debug) std::cout <<"Start" << std::endl;
					break;
				default:
					break;
			}
			break;
	}
}

void GameManager::doGameEvent(SDL_Event e) {
	switch (e.type) {
		case SDL_JOYHATMOTION:

			std::cout << "INPUT MANETTE FRATE" << std::endl;
			// if (e.jaxis.axis == 5)	// LT
			// {
			//
			// 	std::cout << "INPUT MANETTE FRATE" << std::endl;
			// 	// if (e.jaxis.value > -20000)
			// 	// {
			// 	// 	cameraAction = UP;
			// 	// 	return;
			// 	// }
			// }
			// if (e.jaxis.axis == 2)	// RT
			// {
			// 	std::cout << "INPUT MANETTE FRATE" << std::endl;
			// 	// if (e.jaxis.value > -20000)
			// 	// {
			// 	// 	cameraAction = DOWN;
			// 	// 	return;
			// 	// }
			// }
			break;
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
			}
			break;
		case SDL_JOYBUTTONDOWN:
			switch(e.jbutton.button){
				case 0 :	// ENTER
					if(debug) std::cout <<"A" << std::endl;
					break;
				case 1 :	// HIDE MENU
					if(debug) std::cout <<"B" << std::endl;
					break;
				case 2 :	// CAMERA SWITCH
					if(debug) std::cout <<"X"<< std::endl;
					_game->changeCamera();
					break;
				case 3 :	// PAUSE
					if(debug) std::cout <<"Y" << std::endl;
					break;
				case 7 :	// INFOS
					if(debug) std::cout <<"Start" << std::endl;
					goToPause();
					break;
				default:
					break;
			}
			break;
    }
}


void GameManager::doPauseEvent(SDL_Event e) {
	// TODO
	switch (e.type) {
       case SDL_KEYDOWN:
        if (input.togglePause.has(e.key.keysym.sym)) {
					goToGame();
				}
				if (input.up.has(e.key.keysym.sym)){//going up
						_pause.moveSelectors(1);
				}
				if (input.down.has(e.key.keysym.sym)){//going down
						_pause.moveSelectors(-1);
				}
				if(input.select.has(e.key.keysym.sym) && _pause.getPauseMenu() == "QuitToMenu"){
					goToMenu();
				}
				if(input.select.has(e.key.keysym.sym) && _pause.getPauseMenu() == "Continue"){
					goToGame();
				}
        if (debug && e.key.keysym.sym==SDLK_SPACE) {
					goToMenu();
				}
			break;
		case SDL_JOYHATMOTION:
			if (e.jhat.hat == 0){
				switch(e.jhat.value)
				{
					case SDL_HAT_UP:
						_pause.moveSelectors(1);
						if(debug) std::cout << "UP"<< std::endl;
						break;
					case SDL_HAT_DOWN:
						_pause.moveSelectors(-1);
						if(debug) std::cout << "DOWN"<< std::endl;
						break;
					default:
						break;
				}
			}
			break;
			case SDL_JOYBUTTONDOWN:
				switch(e.jbutton.button){
					case 0 :	// ENTER
						if(debug) std::cout <<"A" << std::endl;
						if(_pause.getPauseMenu() == "Continue"){
							goToGame();
						}else{
							goToMenu();
						}
						break;
					case 1 :	// HIDE MENU
						if(debug) std::cout <<"B" << std::endl;
						break;
					case 2 :	// CAMERA SWITCH
						if(debug) std::cout <<"X"<< std::endl;
						_game->changeCamera();
						break;
					case 3 :	// PAUSE
						if(debug) std::cout <<"Y" << std::endl;
						break;
					case 7 :	// INFOS
						if(debug) std::cout <<"Start" << std::endl;
						goToGame();
						break;
					default:
						break;
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
	if (_levelName == "Infinite") {
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
