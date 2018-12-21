#include "splineengine/AssetManager.hpp"

namespace splineengine {

AssetManager::AssetManager()
	:_isLoaded(false)
{
	std::cout << "AssetManager constructor " << std::endl;
//	loadAssets();
}

void AssetManager::loadAssets() {
	std::cout << "AssetManager loaded " << std::endl;
	
	// TODO : make this work :'(
	//_models[PLANEMODEL] = Model("plane");
	// _models[SINGEMODEL] = Model("singe");
	// _models[WHEELBARROWMODEL] = Model("wheelbarrow");

	//AssetManager& assetManager = AssetManager::instance();
	_isLoaded = true;
}




}