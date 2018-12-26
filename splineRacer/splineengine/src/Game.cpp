#include <splineengine/Game.hpp>
#include <splineengine/CubeMap.hpp>

namespace splineengine {

Game::Game()
	:_player(), _spline()
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
    Settings& settings = Settings::instance();

	// TODO : build list from class Obstacle instead of GameObject
	for (float i=0; i<5; ++i) {
        _obstacles.push_back (GameObject(
        	assetManager.models()[PLANEMODEL], _spline, true,
            glm::vec3(i/8,  i, (int)i%8), //glm::vec3(3+i/8, 0.f, 1.5f),
            glm::vec3(0.4f, 0.4f, 0.4f),
            glm::vec3(0.0f, 0.0f, i/5)
        ));

        std::cout << "gameobj  spline pos " << _obstacles[i].sPosition() << std::endl;
    }

    glEnable(GL_DEPTH_TEST);
}


void Game::update() {
	// TODO
}


void Game::render() {
	// TODO

	_renderManager.useProgram(NORMAL);
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	for (float i=0; i<_obstacles.size(); ++i) {

		_renderManager.updateMVMatrix(*_cameras[_chosenCamera], _obstacles[i].matrix());
		_renderManager.applyTransformations(NORMAL, _renderManager.MVMatrix());

	    _obstacles[i].draw();

    }

}


}
