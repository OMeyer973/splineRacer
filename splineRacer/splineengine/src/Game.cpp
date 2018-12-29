#include <splineengine/Game.hpp>
#include <fstream>
// #include <splineengine/CubeMap.hpp>

namespace splineengine {

Game::Game()
	:
	_player(GameObject(AssetManager::instance().models()["plane"], _spline, false, defaultPlayerPos)), 
	_spline(LEVEL_ENDLESS)
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
 	_spline(levelId)
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

	for (float i=0; i<_spline.length(); i+=.3f) {
		_obstacles.push_back(Obstacle(
			GameObject(
				assetManager.models()["cloud"], _spline, true,
				glm::vec3(i, 0, 0), 
				glm::vec3(4*glm::sin(i)+0.2f),
				glm::vec3(glm::cos(i*2.f), 0.f, glm::sin(i))
			)
		));
	}

	for (float i=0; i<_spline.length(); i+=10.f) {
		for (float j = 0; j < 2.5; j+=.5f) {
			_collectables.push_back(Collectable(
				GameObject(
					assetManager.models()["coin"], _spline, false,
					glm::vec3(i+j, 0, 10), 
					glm::vec3(1.f),
					glm::vec3(0.f)
				)
			));
		}
		for (float j = 0; j < 6.28; j+=.1f) {
			_obstacles.push_back(Obstacle(
				GameObject(
					assetManager.models()["skybox"], _spline, true,
					glm::vec3(i-5, j, 15), 
					glm::vec3(1+(int)(30*j)%3),
					glm::vec3(j, -20*j, 3*j)
				)
			));
		}
	}

	glEnable(GL_DEPTH_TEST);
}


void Game::update() {
	// TODO
	// Update player position and speed
	_player.update(Settings::instance().deltaTime());
	
	// Collectables rotation
	for (float i=0; i<_collectables.size(); ++i) {
		_collectables[i].update(Settings::instance().deltaTime(), i);
	}

	// Check for collisions with obstacles
	for (float i=0; i<_obstacles.size(); ++i) {
		_player.collideWith(_obstacles[i]);
	}

	// Check for collisions with collectables
	// for (float i=0; i<_collectables.size(); ++i) {
	// 	_player.collideWith(_collectables[i]);
	// }
}


void Game::render() {
	// TODO
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::mat4 camMatrix = _spline.camMatrix(_player.sPosition());
	glm::mat4 MVMatrix = camMatrix * _player.matrix();

	// Draw the player (hidden in Point Of View Camera)
	if (_chosenCamera != POV_CAMERA) {
		_player.draw(_renderManager, *_cameras[_chosenCamera], camMatrix);
	}

	// Draw obstacles
	for (float i=0; i<_obstacles.size(); ++i) {

		// Get the transform matrix of the current obstacle
		MVMatrix = camMatrix * _obstacles[i].matrix();

		_renderManager.updateMVMatrix(*_cameras[_chosenCamera], MVMatrix);
		_renderManager.useProgram(DIRECTIONAL_LIGHT);

		_obstacles[i].draw();
	}

	// Draw Collectables
	for (float i=0; i<_collectables.size(); ++i) {

		// Get the transform matrix of the current obstacle
		MVMatrix = camMatrix * _collectables[i].matrix();

		_renderManager.updateMVMatrix(*_cameras[_chosenCamera], MVMatrix);
		_renderManager.useProgram(DIRECTIONAL_LIGHT);

		_collectables[i].draw();
	}

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


}
