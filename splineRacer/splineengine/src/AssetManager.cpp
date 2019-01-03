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
	_models.insert(std::make_pair("plane", 			Model("plane",		"planetexture2.jpg")));
	_models.insert(std::make_pair("wheelbarrow",	Model("wheelbarrow","planetexture2.jpg")));
	_models.insert(std::make_pair("singe", 			Model("singe",		"planetexture.jpg")));
	_models.insert(std::make_pair("skybox", 		Model("skybox",		"nuages.png")));
	_models.insert(std::make_pair("cloud", 			Model("cloud",		"cloud.jpg")));
	_models.insert(std::make_pair("coin", 			Model("coin",		"coin.png")));
	_models.insert(std::make_pair("prism", 			Model("prism",		"cloud.jpg")));
	_models.insert(std::make_pair("frontmenu",		Model("frontmenu",	"FrontMenu.png")));
	_models.insert(std::make_pair("menu",			Model("menu",		"Continue.png")));
	_models.insert(std::make_pair("alien",			Model("alien",		"alien.png")));
	_models.insert(std::make_pair("finish_line",	Model("finish_line","finish_line2.jpg")));
}


}
