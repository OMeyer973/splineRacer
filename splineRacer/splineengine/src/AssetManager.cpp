#include "splineengine/AssetManager.hpp"

namespace splineengine {

AssetManager::AssetManager()
{
	if (debug) std::cout << "AssetManager constructor " << std::endl;
	loadAssets();
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
	_models.insert(std::make_pair("Easy",       Model("menu")));
	_models.insert(std::make_pair("Normal",     Model("menu")));
	_models.insert(std::make_pair("Hard",       Model("menu")));
	_models.insert(std::make_pair("Infinite",	Model("menu")));
	_models.insert(std::make_pair("alien",		Model("alien")));
	_models.insert(std::make_pair("finish_line",Model("finish_line")));
}

void AssetManager::setupText() {
	_textManager.setupTTF();
}



}
