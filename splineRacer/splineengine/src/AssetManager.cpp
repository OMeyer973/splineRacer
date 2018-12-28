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
	_models.insert(std::make_pair(PLANEMODEL, Model("plane", "planetexture2.jpg")));
	_models.insert(std::make_pair(WHEELBARROWMODEL, Model("wheelbarrow", "planetexture2.jpg")));
	_models.insert(std::make_pair(SINGEMODEL, Model("singe", "planetexture.jpg")));
	_models.insert(std::make_pair(SKYBOXMODEL, Model("skybox", "skurt.png")));
	_models.insert(std::make_pair(CLOUDMODEL, Model("cloud", "cloud.jpg")));
	_models.insert(std::make_pair(COINMODEL, Model("coin", "coin.png")));
}


}