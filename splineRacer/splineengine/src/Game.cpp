#include <splineengine/Game.hpp>
#include <fstream>
// #include <splineengine/CubeMap.hpp>

namespace splineengine {

Game::Game()
	:
	_player(GameObject(
		AssetManager::instance().models()[PLANEMODEL], _spline, false,
		glm::vec3(0, 0, 10),
		glm::vec3(1.f, 1.f, 1.f),
		glm::vec3(0.f, 0.f, 0.f)
	)), 
	_spline()
{
	std::cout << "infinite game constructor called " << std::endl;
	_cameras.emplace_back(new POVCamera());
	_cameras.emplace_back(new TrackballCamera());
	_chosenCamera = TRACKBALL_CAMERA;

	RenderManager _renderManager(*_cameras[_chosenCamera]);
}

Game::Game(int levelId)
	:_player(), _spline(levelId)
{
	// TODO
	std::cout << "game from level constructor called " << std::endl;
}


Game::~Game() {
	std::cout << "game destructor called " << std::endl;
}


void Game::loadLevel(int levelId) {
	// TODO : fix & finish
	std::string mapPath = Settings::instance().appPath().dirPath()
		+ ("../../splineRacer/assets/levels/level" + std::to_string(levelId) +".map");

	std::cout << "loading level from file : " << mapPath << std::endl;
	std::ifstream i(mapPath);
	
	std::string line;

	// cf https://github.com/nlohmann/json#examples
	nlohmann::json map;
	i >> map;
	std::cout << "loaded json map : " << map << std::endl;

}

void Game::loadLevel() {
	// TODO
	AssetManager& assetManager = AssetManager::instance();

	// TODO : build list from class Obstacle instead of GameObject
	for (float i=0; i<_spline.length(); i+=.3f) {
        _obstacles.push_back (GameObject(
        	assetManager.models()[SINGEMODEL], _spline, true,
            glm::vec3(i, i, 0.f), // glm::vec3(i/8,  i, (int)i%8), //glm::vec3(3+i/8, 0.f, 1.5f),
            glm::vec3(.5f, .5f, .5f),
            glm::vec3(0.f, 0.f, 0.f)
        ));

        // std::cout << "gameobj spline pos " << _obstacles[i].sPosition() << std::endl;
    }

    glEnable(GL_DEPTH_TEST);
}


void Game::update() {
	// TODO
	// Update player position and speed
	_player.update(Settings::instance().deltaTime());
	
	// check for collisions
	for (float i=0; i<_obstacles.size(); ++i) {
		_player.collideWith(_obstacles[i]);
	}
}


void Game::render() {
	// TODO
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::mat4 camMatrix = _spline.camMatrix(_player.sPosition());
	glm::mat4 MVMatrix = camMatrix * _player.matrix();

	// Update MVMatrix according to the object's transformation
	_renderManager.updateMVMatrix(*_cameras[_chosenCamera], MVMatrix);
	_renderManager.useProgram(DIRECTIONAL_LIGHT);
	_renderManager.applyTransformations(DIRECTIONAL_LIGHT, _renderManager.MVMatrix());

	// Draw the player (hidden in Point Of View Camera)
	if (_chosenCamera != POV_CAMERA) {
		_player.draw();
	}

	// Draw obstacles
	for (float i=0; i<_obstacles.size(); ++i) {

		// Get the transform matrix of the current obstacle
		MVMatrix = camMatrix * _obstacles[i].matrix();

		_renderManager.updateMVMatrix(*_cameras[_chosenCamera], MVMatrix);
		_renderManager.useProgram(DIRECTIONAL_LIGHT);
		_renderManager.applyTransformations(DIRECTIONAL_LIGHT, _renderManager.MVMatrix());
	    _obstacles[i].draw();
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
