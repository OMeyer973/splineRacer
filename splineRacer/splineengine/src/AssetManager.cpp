#include <splineengine/AssetManager.hpp>
#include <splineengine/Settings.hpp>

#include <memory>

namespace splineengine {


AssetManager::AssetManager()
	
{
	std::cout << "AssetManager constructor " << std::endl;
	//loadAssets();
}

void AssetManager::loadAssets() {
	_models[PLANEMODEL] = Model("plane");
	_models[SINGEMODEL] = Model("singe");
	_models[WHEELBARROWMODEL] = Model("wheelbarrow");

	_isLoaded = true;
}




}