#include <splineengine/Game.hpp>
#include <fstream>
#include <iostream>
#include "splineengine/Error.hpp"
#include <cstdlib>

namespace splineengine {

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTORS
////////////////////////////////////////////////////////////////////////////////////////////////////////////

Game::Game()
	:
	_gameMode(ENDLESS),
	_spline("Endless"),
	_player(GameObject(
		AssetManager::instance().models()["plane"],
		_spline,
		"planetexture2.jpg",
		 false,
		Transform(defaultPlayerPos)
	), defaultPlayerMaxSpeed * (1.f-endlessSpeedMultiplier)), // creation of the firs map part will increase the speed back to 1
	_skybox(GameObject(
		AssetManager::instance().models()["skybox"],
		_spline,
		"skybox_desert.png",
		 true,
		Transform(glm::vec3(0.f), glm::vec3(100.f))
	)),
	_maxCollideDistance(endlessMaxCollideDistance),
	_maxRenderDistance(endlessMaxRenderDistance),
	_alien(
		GameObject(
			AssetManager::instance().models()["alien"],
			_spline,
			"alien.png",
			false,
			Transform(glm::vec3(0.f), glm::vec3(0.3f))
		),
		_player
	),
	_finishLine(GameObject( // will not be displayed in Endless anyway
		AssetManager::instance().models()["finish_line"],
		_spline,
		"finish_line2.jpg",
		 true,
		Transform()
	))
{
	std::cout << "infinite game constructor called " << std::endl;
	_cameras.emplace_back(new POVCamera());
	_cameras.emplace_back(new TrackballCamera());
	_chosenCamera = TRACKBALL_CAMERA;
	RenderManager _renderManager(*_cameras[_chosenCamera]);

	generateLevel(0.f, _spline.length(), 0); // first generation is always with rings
}


Game::Game(const std::string& levelName)
	:
	_gameMode(CLASSIC),
	_spline(levelName),
	_player(GameObject(
		AssetManager::instance().models()["plane"],
		_spline,
		"planetexture2.jpg",
		 false,
		Transform(defaultPlayerPos)
	)),
	_skybox(GameObject(
		AssetManager::instance().models()["skybox"],
		_spline,
		"skybox_desert.png",
		true,
		Transform(glm::vec3(0.f), glm::vec3(100.f))
	)),
	_maxCollideDistance(levelMaxCollideDistance),
	_maxRenderDistance(levelMaxRenderDistance),
	_alien(
		GameObject(
			AssetManager::instance().models()["alien"],
			_spline,
			"alien.png",
			false,
			Transform(glm::vec3(0.f), glm::vec3(0.3f))
		),
		_player
	),
	_finishLine(GameObject(
		AssetManager::instance().models()["finish_line"],
		_spline,
		"finish_line2.jpg",
		 false,
		Transform(glm::vec3(0.f), glm::vec3(8.f))
	))
{
	// TODO - OK now ?
	std::cout << "game constructor from level caled : " << levelName << std::endl;
	_cameras.emplace_back(new POVCamera());
	_cameras.emplace_back(new TrackballCamera());
	_chosenCamera = TRACKBALL_CAMERA;
	RenderManager _renderManager(*_cameras[_chosenCamera]);

	loadLevel(levelName);
}


Game::~Game() {
	std::cout << "game destructor called " << std::endl;
	GameObject::resetDrawing();
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////
// LEVEL LOADING & CONSTRUCTION STUFF
////////////////////////////////////////////////////////////////////////////////////////////////////////////

GameObject Game::gameObjFromJson(nlohmann::json j) {
	AssetManager& assetManager = AssetManager::instance();
	
	AnimationList animList;
	for (uint i=1; i<=nbAnimInJson; i++) {
		// if to clean bad values in unregistered fields
		if (j["anim" + std::to_string(i)].is_number()) {
			std::cout << j["anim" + std::to_string(i)].get<int>() << std::endl;
			animList.emplace_back(j["anim" + std::to_string(i)].get<int>()); 
		}
	}

	std::string textureName = "default.png";
	if(j["texture"].is_string()) {
		textureName = j["texture"].get<std::string>();
	}

	return GameObject(
		assetManager.models()[ j["model"].get<std::string>() ], // model
		_spline, // spline
		textureName,
		j["is_static"].get<bool>(), //isStatic
		Transform(
			glm::vec3(j["pos_fwd"].get<float>(),   j["pos_left"].get<float>(),   j["pos_up"].get<float>()), // sPosition
			glm::vec3(j["scale_fwd"].get<float>(), j["scale_left"].get<float>(), j["scale_up"].get<float>()), // scale
			glm::vec3(j["rot_fwd"].get<float>(),   j["rot_left"].get<float>(),   j["rot_up"].get<float>()) // rotation
		),
		animList
	);
}


void Game::loadLevel(const std::string& levelName) {
	// TODO : finish & polish, add decoration. load spline from JSON
	std::string mapPath = Settings::instance().appPath().dirPath()
		+ ("../../splineRacer/assets/levels/" + levelName + ".map");

	if (debug) std::cout << "loading level from file : " << mapPath << std::endl;
	
	// TODO : check for exception
	std::ifstream mapStream(mapPath);
	if (mapStream.fail()) {
		throw(Error("tried to read invalid map json file",__FILE__, __LINE__));
	}

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

	// tmp?
	AssetManager& assetManager = AssetManager::instance();
	for (float i=-1; i<_spline.length()+1; i+=1.f) {
		_obstacles.push_back(Obstacle(GameObject(
			assetManager.models()["prism"], _spline,
			"cloud.jpg",
			true,
			Transform(
				glm::vec3(i, 0, 0),
				glm::vec3(4.f),
				glm::vec3(glm::cos(i*2.f), 0.f, glm::sin(i))
			)
		)));
	}

	_finishLine.sPosition() = glm::vec3(_spline.length(), 0.f, 0.f);

	_renderManager.initGameLights();

	// sort game object lists
	orderObjListFwd(_obstacles);
	orderObjListFwd(_collectables);
	orderObjListFwd(_decorations);

	glEnable(GL_DEPTH_TEST);
}


void Game::generateLevel(const float start, const float finish, const int partToGenerate) {
	// TODO
	AssetManager& assetManager = AssetManager::instance();


	// base clouds
	for (float i=start; i<finish; i+=.7f) {
		_obstacles.push_back(Obstacle(GameObject(
			assetManager.models()["prism"], _spline,
			"cloud.jpg",
			true,
			Transform(
				glm::vec3(i, 0, 0),
				glm::vec3((2.f*glm::sin(i)) + 4.f),
				glm::vec3(glm::cos(i*2.f), 0.f, glm::sin(i))
			)
		)));
	}

	// base coins
	for (float i=start; i<finish; i+=10.f) {
		for (float j = 0; j < 2.5; j+=.5f) {
			for (float k = 0; k <= .2f; k+=.2f) {
				if (i+j < finish) {
					_collectables.push_back(Collectable(GameObject(
						assetManager.models()["coin"], _spline,
						"coin.png",
						false,
						Transform(
							glm::vec3(i+j, -(i+k), 10),
							glm::vec3(3.f),
							glm::vec3(0)
						),
						{ ROT_CONST_UP }
					)));
				}
			}
		}
	}	
	float chunkStart = start + 5.f;
	float chunkFinish = finish - 5.f;
	switch (partToGenerate) {
		case 0 : //moving rings
			for (float i=chunkStart; i< chunkFinish; i+=10.f) { // full rings on the chunk
				for (float j = 0; j < 2.f * M_PI; j+=.3f) { // ring perimeter
					_obstacles.push_back(Obstacle(GameObject(
						assetManager.models()["prism"], _spline,
						"cloud.jpg",
						 false,
						Transform(
							glm::vec3(i, j, 15),
							glm::vec3(3),
							j * leftVec
						),
						{ MOVE_CONST_LEFT, ROT_CONST_LEFT, MOVE_SIN_UP }
					)));
				}
			}
			break;
		case 1 : //spiral
			for (float i=chunkStart; i<chunkFinish; i+=30.f) {// full spirals on the chunk
				for (float j = 0; j < 2.f * M_PI; j+=.4f) { // spiral parts - length
					float fwdPos = i+4.f*j;
					if (fwdPos < chunkFinish) {
						_obstacles.push_back(Obstacle(GameObject(
							assetManager.models()["prism"], _spline,
							"cloud.jpg",
							 true,
							Transform(
								glm::vec3(fwdPos, j, maxPlayerUp - minPlayerUp),
								glm::vec3((maxPlayerUp - minPlayerUp)),
								glm::vec3(0.f)
							)
						)));
					}
				}
			}
			break;
		case 2 : //random towers
			for (float i=chunkStart; i<finish; i+=1.5f) {// full tower
				float towerLeft = glm::linearRand(0.f,2.f*float(M_PI));
				for (float h = minPlayerUp; h < maxPlayerUp+4; h+=6) { // height
					_obstacles.push_back(Obstacle(GameObject(
						assetManager.models()["prism"], _spline,
						"cloud.jpg",
						 true,
						Transform(
							glm::vec3(i, towerLeft, h),
							glm::vec3(4),
							glm::vec3(0,i,i)
						)
					)));
				}
			}
			break;
		case 3 : //full random objects
			for (float i=chunkStart; i<finish; i+=1.f) {// random object
				_obstacles.push_back(Obstacle(GameObject(
					assetManager.models()["prism"], _spline,
					"cloud.jpg",
					 false,
					Transform(
						glm::vec3(i, glm::linearRand(0.f,2.f*float(M_PI)), glm::linearRand(minPlayerUp, maxPlayerUp)),
						glm::vec3(4),
						glm::vec3(i, 0 , -i)
					),
					{ ROT_CONST_UP }
				)));
			}
			break;
	}

	orderObjListFwd(_obstacles);
	orderObjListFwd(_collectables);
	orderObjListFwd(_decorations);

	_renderManager.initGameLights();

	glEnable(GL_DEPTH_TEST);
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////
// RENDER & UPDATE LOOPs
////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Game::update() {
	// TODO
	//PHYSICS UPDATE
	// Update player position and speed
	_player.update();
	// Update alien position and speed
	_alien.update();

	// Collectables animation
	// for (std::list<Collectable>::iterator it = _collectables.begin(); it != _collectables.end(); ++it) {
	// 	(*it).update(dt, 0, _player.sPosition());
	// }

	// Check for collisions with obstacles
	updateObstacleList(_obstacles);
	// Check for collisions with collectables
	updateCollectableList(_collectables);

	// Update camera
	if (_chosenCamera == TRACKBALL_CAMERA) {
		_cameras[_chosenCamera]->update();
	}

	// ADD LENGTH TO THE SPLINE IF NECESSARY
	if (_gameMode == ENDLESS && _spline.length() - _player.sPosition()[FWD] < _maxRenderDistance) {
		float oldLength = _spline.length();
		while (_spline.length() < oldLength + _maxRenderDistance) {
			_spline.addAnchor();
		}
		generateLevel(oldLength, _spline.length(), rand()%nbOfRandomCHunks);
		if (debug) std::cout << "player speed increased" << std::endl;
		_player.increaseSpeed();
	}

	// END OF GAME LOGIC CHECKS
	if (_gameState == LEVELWIN || _gameState == LEVELLOSE || _gameState == ENDLESSOVER) {
		if (_endScreenTimer <= 0) {
			_gameState = EXITING;
			if (debug) std::cout << "gameState : EXITING (going back to menu)" << std::endl;
		}
		_endScreenTimer -= Settings::instance().deltaTime();
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
	else if (_player.sPosition()[FWD] > _finishLine.sPosition()[FWD] && _gameMode == CLASSIC) {
		if (debug) std::cout << "Level is won" << std::endl;
		_gameState = LEVELWIN;
		_alien.chasingPlayer() = false;
	}
}


void Game::render() {
	// TODO
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_renderManager.splineCamMatrix() = _spline.camMatrix(_player.sPosition());
	glm::mat4 MVMatrix = _renderManager.splineCamMatrix();

	_renderManager.updateMVMatrix(*_cameras[_chosenCamera], MVMatrix, _player.scale());

	_renderManager.updateGlobalMatrix(); // celui là est nécéssaire !
	_renderManager.updateGameLights();

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
	for (std::list<Obstacle>::iterator it = _obstacles.begin(); it != _obstacles.end(); ++it) {
		if (glm::abs(it->sPosition()[FWD] - _player.sPosition()[FWD]) < _maxRenderDistance) {
			_renderManager.drawObject(*it, *_cameras[_chosenCamera]);
		}
	}

	// Draw Collectables
	for (std::list<Collectable>::iterator it = _collectables.begin(); it != _collectables.end(); ++it) {
		if (!(*it).isHidden()) {
			if (glm::abs(it->sPosition()[FWD] - _player.sPosition()[FWD]) < _maxRenderDistance) {
				_renderManager.drawObject(*it, *_cameras[_chosenCamera]);
			}
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
	if (_gameState == LEVELWIN)
		_renderManager.drawWinCard();

	if (_gameState == LEVELLOSE) 
		_renderManager.drawLoseCard();

	if (_gameState == ENDLESSOVER)
		_renderManager.drawLoseCard();

	_renderManager.drawDistanceToAlien(_player.sPosition()[FWD] - _alien.sPosition()[FWD]);

	_renderManager.drawScore(_player.score());

}


////////////////////////////////////////////////////////////////////////////////////////////////////////////
// SMALL FUNCTIONS
////////////////////////////////////////////////////////////////////////////////////////////////////////////


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

template <typename T>
void Game::orderObjListFwd (std::list<T>& objList) {
	objList.sort([](T objA, T objB) {return objA.sPosition()[FWD] < objB.sPosition()[FWD];});
}


template <typename T, typename U>
void Game::handleCollision(T& firstObject, U& secondObject) {
	if (firstObject.intersect(secondObject)) {
		firstObject.doCollisionWith(secondObject);
		secondObject.doCollisionWith(firstObject);
	}
}

void Game::updateObstacleList (std::list<Obstacle>& objList) {
	for (typename std::list<Obstacle>::iterator it = objList.begin(); it != objList.end(); ++it) {
		// if the object is near enough to the player : check collision
		if (glm::abs(it->sPosition()[FWD] - _player.sPosition()[FWD]) < _maxCollideDistance) {
			it->update();
			handleCollision(_player, *it);
		// else, if the object is in front of the player, discard all the next objects (lists are ordered)
		} else if (it->sPosition()[FWD] > _player.sPosition()[FWD]) {
			break;
		}
	}
}

void Game::updateCollectableList (std::list<Collectable>& objList) {
	typename std::list<Collectable>::iterator it = objList.begin();
	while (it != objList.end()) {
		// if the object is near enough to the player : check collision
		if (glm::abs(it->sPosition()[FWD] - _player.sPosition()[FWD]) < _maxCollideDistance) {
			it->update(_player.sPosition());
			handleCollision(_player, *it);
		// else, if the object is in front of the player, discard all the next objects (lists are ordered)
		} else if (it->sPosition()[FWD] > _player.sPosition()[FWD]) {
			break;
		}

		if (it->isHidden()) {
			objList.erase(it++);
		} else {
			++it;
		}
	}
}

template <typename T>
void Game::renderObjList(std::list<T>& objList) {
	typename std::list<T>::iterator it = objList.begin();
	while (it != objList.end()) {
		// if the object is near enough to the player : render the object
		if (glm::abs(it->sPosition()[FWD] - _player.sPosition()[FWD]) < _maxRenderDistance) {
			_renderManager.drawObject(*it, *_cameras[_chosenCamera]);
			++it;
		// else, if the object is in behind the player, we can remove it
		} else if (it->sPosition()[FWD] < _player.sPosition()[FWD]) {
	        objList.erase(it++);
		}
	}
}

}