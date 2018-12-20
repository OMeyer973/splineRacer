#include <splineengine/Game.hpp>


namespace splineengine {

Game::Game()
	:_player(), _spline()
{
	std::cout << "infinite game constructor called " << std::endl;
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
	//AssetManager& assetManager = AssetManager::instance();
    for (float i=0; i<100; ++i) {
        obstacles.push_back (GameObject(
        	Model(),
            //assetManager.models()[PLANEMODEL],
            glm::vec3(3+i/8, 0.f, 1.5f),
            glm::vec3(0.4f, 0.4f, 0.4f),
            glm::vec3(0.0f, 0.0f, i/5)
        ));
    }
}


void Game::update() {
	// TODO
}


void Game::render() {
	// TODO
}


}