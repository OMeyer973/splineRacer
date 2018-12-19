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
	std::cout << "game from level constructor called " << std::endl;
}


Game::~Game() {
	std::cout << "game destructor called " << std::endl;
}
void Game::loadLevel() {

}


void Game::update() {
	// TODO
}


void Game::render() {
	// TODO
}


}