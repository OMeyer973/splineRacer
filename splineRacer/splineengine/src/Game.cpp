#include <splineengine/Game.hpp>
// #include <splineengine/CubeMap.hpp>

namespace splineengine {

Game::Game()
	:
	_player(GameObject(AssetManager::instance().models()[PLANEMODEL], _spline, false)), 
	_spline()
{
	std::cout << "infinite game constructor called " << std::endl;
	_cameras.emplace_back(new POVCamera());
	_cameras.emplace_back(new TrackballCamera());
	_chosenCamera = TRACKBALL_CAMERA;

	RenderManager _renderManager(*_cameras[_chosenCamera]);
}

Game::Game(std::string levelName)
	:_player(), _spline(levelName)
{
	// TODO
	std::cout << "game from level constructor called " << std::endl;
}


Game::~Game() {
	std::cout << "game destructor called " << std::endl;
}


void Game::loadLevel(std::string levelName) {
	// TODO
}

void Game::loadLevel() {
	// TODO
	AssetManager& assetManager = AssetManager::instance();

	// TODO : build list from class Obstacle instead of GameObject
	for (float i=0; i<10; ++i) {
        _obstacles.push_back (GameObject(
        	assetManager.models()[SINGEMODEL], _spline, true,
            glm::vec3(i/8, i/16, 0), // glm::vec3(i/8,  i, (int)i%8), //glm::vec3(3+i/8, 0.f, 1.5f),
            glm::vec3(1.f, 1.f, 1.f),
            glm::vec3(0.0f, 0.0f, i/5)
        ));

        std::cout << "gameobj  spline pos " << _obstacles[i].sPosition() << std::endl;
    }

    glEnable(GL_DEPTH_TEST);
}


void Game::update() {
	// TODO
	_player.update(Settings::instance().deltaTime()/100);
}


void Game::render() {
	// TODO
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::mat4 camMatrix = _spline.camMatrix(_player.sPosition());

	glm::mat4 MVMatrix = camMatrix * _player.matrix();

	// Update MVMatrix according to the object's transformation
	_renderManager.updateMVMatrix(*_cameras[_chosenCamera], MVMatrix);
	_renderManager.useProgram(NORMAL);
	_renderManager.applyTransformations(NORMAL, _renderManager.MVMatrix());

	_player.draw();

	for (float i=0; i<_obstacles.size(); ++i) {

		// get the transform matrix of the object
		MVMatrix = camMatrix * _obstacles[i].matrix();

		_renderManager.updateMVMatrix(*_cameras[_chosenCamera], MVMatrix);
		_renderManager.useProgram(NORMAL);
		_renderManager.applyTransformations(NORMAL, _renderManager.MVMatrix());

	    _obstacles[i].draw();

    }

}


}
