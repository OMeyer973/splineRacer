#include "splineengine/AssetManager.hpp"

namespace splineengine {

AssetManager::AssetManager()
{
	if (debug) std::cout << "AssetManager constructor " << std::endl;
	loadAssets();
	std::cout << "Number of joysticks : " << SDL_NumJoysticks() << std::endl;
	SDL_InitSubSystem(SDL_INIT_JOYSTICK);

	if (SDL_NumJoysticks() > 0) {
    // Open joystick
    _joystick = SDL_JoystickOpen(0);

    if (_joystick) {
        // printf("Opened Joystick 0\n");
        // printf("Name: %s\n", SDL_JoystickIndex(0));
        // printf("Number of Axes: %d\n", SDL_JoystickNumAxes(_joystick));
        // printf("Number of Buttons: %d\n", SDL_JoystickNumButtons(_joystick));
        // printf("Number of Balls: %d\n", SDL_JoystickNumBalls(_joystick));
    } else {
        printf("Couldn't open Joystick 0\n");
    }
}

}

void AssetManager::loadAssets() {
	if (debug) std::cout << "AssetManager : Load assets" << std::endl;

	// TODO : load actual assets for the game
	_models.insert(std::make_pair("plane", 		Model("plane")));
	_models.insert(std::make_pair("wheelbarrow",Model("wheelbarrow")));
	_models.insert(std::make_pair("singe", 		Model("singe")));
	_models.insert(std::make_pair("skybox", 	Model("skybox")));
	_models.insert(std::make_pair("cloud", 		Model("cloud")));
	_models.insert(std::make_pair("coin", 		Model("coin")));
	_models.insert(std::make_pair("prism", 		Model("sphere")));
	_models.insert(std::make_pair("frontmenu",	Model("frontmenu")));
	_models.insert(std::make_pair("menu",		Model("menu")));
	_models.insert(std::make_pair("alien",		Model("alien")));
	_models.insert(std::make_pair("finish_line",Model("finish_line")));
	_models.insert(std::make_pair("clouds",Model("clouds")));
	_models.insert(std::make_pair("tower",Model("tower")));
}

void AssetManager::setupText() {
	_textManager.setupTTF();
}



}
