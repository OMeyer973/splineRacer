#include "splineengine/AssetManager.hpp"

namespace splineengine {

bool AssetManager::_isLoaded;

AssetManager::AssetManager()
{
	std::cout << "AssetManager constructor " << std::endl;
	loadAssets();
}

void AssetManager::loadAssets() {
	// _models[PLANEMODEL] = Model("plane");
	// _models[SINGEMODEL] = Model("singe");
	// _models[WHEELBARROWMODEL] = Model("wheelbarrow");

	//AssetManager& assetManager = AssetManager::instance();
	_isLoaded = true;
}




}