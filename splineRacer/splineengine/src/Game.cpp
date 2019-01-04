#include <splineengine/Game.hpp>
#include <fstream>
#include <iostream>

namespace splineengine {

Game::Game()
	:
	_player(GameObject(AssetManager::instance().models()["plane"], _spline, false, defaultPlayerPos)),
	_spline(LEVEL_ENDLESS),
	_gameMode(ENDLESS),
	_skybox(GameObject(AssetManager::instance().models()["skybox"], _spline, true, glm::vec3(0.f), glm::vec3(100.f), glm::vec3(0.f))),
	_alien(GameObject(AssetManager::instance().models()["alien"], _spline, false, defaultPlayerPos, glm::vec3(.3f)), _player),
	_finishLine(GameObject(AssetManager::instance().models()["finish_line"], _spline, true, glm::vec3(0.f), glm::vec3(6.f), glm::vec3(0.f)))
{
	std::cout << "infinite game constructor called " << std::endl;
	_cameras.emplace_back(new POVCamera());
	_cameras.emplace_back(new TrackballCamera());
	_chosenCamera = TRACKBALL_CAMERA;
	RenderManager _renderManager(*_cameras[_chosenCamera]);
}


Game::Game(int levelId)
	:
	_player(GameObject(AssetManager::instance().models()["plane"], _spline, false, defaultPlayerPos)),
	_spline(levelId),
	_gameMode(CLASSIC),
	_skybox(GameObject(AssetManager::instance().models()["skybox"], _spline, true, glm::vec3(0.f), glm::vec3(100.f), glm::vec3(0.f))),
	_alien(GameObject(AssetManager::instance().models()["skybox"], _spline, false, defaultPlayerPos, glm::vec3(2.f)), _player),
	_finishLine(GameObject(AssetManager::instance().models()["finish_line"], _spline, false, glm::vec3(0.f), glm::vec3(1.f), glm::vec3(0.f)))
{
	// TODO - OK now ?
	std::cout << "game from level constructor called " << std::endl;
	_cameras.emplace_back(new POVCamera());
	_cameras.emplace_back(new TrackballCamera());
	_chosenCamera = TRACKBALL_CAMERA;
	RenderManager _renderManager(*_cameras[_chosenCamera]);
}


Game::~Game() {
	std::cout << "game destructor called " << std::endl;
}


GameObject Game::gameObjFromJson(nlohmann::json j) {
	AssetManager& assetManager = AssetManager::instance();
	return GameObject(
		assetManager.models()[ j["model"].get<std::string>() ], // model
		_spline, // spline
		j["is_static"].get<bool>(), //isStatic
		glm::vec3(j["pos_fwd"].get<float>(),   j["pos_left"].get<float>(),   j["pos_up"].get<float>()), // sPosition
		glm::vec3(j["scale_fwd"].get<float>(), j["scale_left"].get<float>(), j["scale_up"].get<float>()), // scale
		glm::vec3(j["rot_fwd"].get<float>(),   j["rot_left"].get<float>(),   j["rot_up"].get<float>()) // rotation
	);
}


void Game::loadLevel(int levelId) {
	// TODO : finish & polish, add decoration. load spline from JSON
	std::string mapPath = Settings::instance().appPath().dirPath()
		+ ("../../splineRacer/assets/levels/level" + std::to_string(levelId) +".map");

	if (debug) std::cout << "loading level from file : " << mapPath << std::endl;
	std::ifstream mapStream(mapPath);

	// cf https://github.com/nlohmann/json#examples
	nlohmann::json map;
	mapStream >> map;

	for (nlohmann::json::iterator it = map.begin(); it != map.end(); ++it) {

		if ((*it)["type"].get<std::string>() == "obstacle") {
			_obstacles.push_back(Obstacle(gameObjFromJson(*it)));
		}
		if ((*it)["type"].get<std::string>() == "collectable") {
			_collectables.push_back(Collectable(gameObjFromJson(*it)));
		}
	}

	glEnable(GL_DEPTH_TEST);
}

void Game::loadLevel() {
	// TODO
	AssetManager& assetManager = AssetManager::instance();

	_finishLine.sPosition() = glm::vec3(_spline.length(), 0.f, 0.f);

	for (float i=0; i<_spline.length(); i+=.3f) {
		_obstacles.push_back(Obstacle(
			GameObject(
				assetManager.models()["prism"], _spline, true,
				glm::vec3(i, 0, 0),
				glm::vec3((2*glm::sin(i)+0.2f) + 4.f),
				glm::vec3(glm::cos(i*2.f), 0.f, glm::sin(i))
			)
		));
		// _obstacles.push_back(Obstacle(
		// 	GameObject(
		// 		assetManager.models()["cloud"], _spline, true,
		// 		glm::vec3(i, 0, 0),
		// 		glm::vec3(1.f, 1.f, 1.f),
		// 		glm::vec3(glm::cos(i*2.f), 0.f, glm::sin(i))
		// 	)
		// ));
	}

	for (float i=0; i<_spline.length(); i+=10.f) {
		for (float j = 0; j < 2.5; j+=.5f) {
			for (float k = 0; k <= .2f; k+=.2f) {
				_collectables.push_back(Collectable(
					GameObject(
						assetManager.models()["coin"], _spline, false,
						glm::vec3(i+j, -(i+k), 10),
						glm::vec3(3.f),
						glm::vec3(0)
					)
				));
			}
		}
		for (float j = 0; j < 6.28; j+=.3f) {
			_obstacles.push_back(Obstacle(
				GameObject(
					assetManager.models()["prism"], _spline, true,
					glm::vec3(i-5, j, 15), 
					glm::vec3(3),
					glm::vec3(j, -20*j, 3*j)
				)
			));
		}
	}

	glEnable(GL_DEPTH_TEST);
}


void Game::update() {
	// TODO
	//PHYSICS UPDATE
	float dt = Settings::instance().deltaTime();
	// Update player position and speed
	_player.update(dt);
	_alien.update(dt);
	
	// Collectables animation
	for (float i=0; i<_collectables.size(); ++i) {
		_collectables[i].update(dt, i, _player.sPosition());
	}

	// Check for collisions with obstacles
	for (std::vector<Obstacle>::iterator it = _obstacles.begin(); it != _obstacles.end(); ++it) {
		handleCollision(_player, *it);
	}

	// Check for collisions with collectables
	for (std::vector<Collectable>::iterator it = _collectables.begin(); it != _collectables.end(); ++it) {
		handleCollision(_player, *it);
	}

	// Update camera
	if (_chosenCamera == TRACKBALL_CAMERA) {
		_cameras[_chosenCamera]->update();
	}

	// END OF GAME LOGIC CHECKS
	if (_gameState == LEVELWIN || _gameState == LEVELLOSE || _gameState == ENDLESSOVER) {
		if (_endScreenTimer <= 0) {
			_gameState = EXITING;
			if (debug) std::cout << "gameState : EXITING (going back to menu)" << std::endl;
		}
		_endScreenTimer -= dt;
	}
	else if (_player.sPosition()[FWD] > _finishLine.sPosition()[FWD]) {
		if (_gameMode == CLASSIC) {
			if (debug) std::cout << "Level is won" << std::endl;
			_gameState = LEVELWIN;
		} 

	}
	else if (_alien.sPosition()[FWD] > _player.sPosition()[FWD]) {
		_player.doCollisionWith(_alien);
		_alien.doCollisionWith(_player);

		if (_gameMode == CLASSIC) {
			if (debug) std::cout << "Level is lost" << std::endl;
			_gameState = LEVELLOSE;
		} 
		
		else if (_gameMode == ENDLESS) {
			if (debug) std::cout << "endless mode is over" << std::endl;
			_gameState = ENDLESSOVER;
		}
	}
}


void Game::render() {
	// TODO
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_renderManager.splineCamMatrix() = _spline.camMatrix(_player.sPosition());
	glm::mat4 MVMatrix = _renderManager.splineCamMatrix();

	_renderManager.updateMVMatrix(*_cameras[_chosenCamera], MVMatrix, _player.scale());
	_renderManager.updateGlobalMatrix(); // celui là est nécéssaire !

	// Draw the player (hidden in Point Of View Camera)
	if (_chosenCamera != POV_CAMERA) {
		_player.draw(_renderManager, *_cameras[_chosenCamera]);
	}

	// Draw the finish line in classic mode
	if (_gameMode == CLASSIC) {
		_renderManager.drawObject(_finishLine, *_cameras[_chosenCamera]);
	}

	// Draw the alien
	_renderManager.drawObject(_alien, *_cameras[_chosenCamera]);

	// Draw obstacles
	for (std::vector<Obstacle>::iterator it = _obstacles.begin(); it != _obstacles.end(); ++it) {
		_renderManager.drawObject(*it, *_cameras[_chosenCamera]);
	}

	// Draw Collectables
	for (std::vector<Collectable>::iterator it = _collectables.begin(); it != _collectables.end(); ++it) {
		if (!(*it).isHidden()) {
			_renderManager.drawObject(*it, *_cameras[_chosenCamera]);
		}
	}

	// Draw _skybox
	glDepthMask(GL_FALSE);
	MVMatrix = _renderManager.splineCamMatrix();
	MVMatrix = glm::translate(MVMatrix, _spline.point(_player.sPosition()[FWD]));
	
	_renderManager.updateMVMatrix(*_cameras[_chosenCamera], MVMatrix, _skybox.scale());
	_renderManager.useProgram(TEXTURE);
	_skybox.draw();
	glDepthMask(GL_TRUE);

	// TODO : display the end cards under these conditions
	// if (_gameState == LEVELWIN)
	// if (_gameState == LEVELLOSE)
	// if (_gameState == ENDLESSOVER)

}


void Game::moveCameraX(const float dx) {
	_cameras[_chosenCamera]->rotateLeft(dx * cameraRotateSpeed);
}

void Game::moveCameraY(const float dy) {
	_cameras[_chosenCamera]->rotateUp(dy * cameraRotateSpeed);
}

void Game::changeCamera() {
	_chosenCamera = (_chosenCamera + 1)  % NUMBER_OF_CAMERAS;
}

void Game::zoomCamera(const float dz) {
	if (_chosenCamera == TRACKBALL_CAMERA) {
		_cameras[_chosenCamera]->moveFront(dz);
	}
}

template <typename T, typename U>
void Game::handleCollision(T& firstObject, U& secondObject) {
	if (firstObject.intersect(secondObject)) {
		firstObject.doCollisionWith(secondObject);
		secondObject.doCollisionWith(firstObject);
	}
}

}
