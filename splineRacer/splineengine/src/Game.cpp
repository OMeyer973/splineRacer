#include <splineengine/Game.hpp>


namespace splineengine {

Game::Game()
	:_player()
{
	std::cout << "game constructor called " << std::endl;
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