#include "splineengine/AssetManager.hpp"

namespace splineengine {

AssetManager::AssetManager()
{
	std::cout << "AssetManager constructor " << std::endl;
	loadAssets();
	loadPrograms();
}

void AssetManager::loadAssets() {
	std::cout << "AssetManager loaded " << std::endl;
	
	// TODO : load actual assets for the game
	_models[PLANEMODEL] = Model("plane");
	_models[SINGEMODEL] = Model("singe");
	_models[WHEELBARROWMODEL] = Model("wheelbarrow");
}

void AssetManager::loadPrograms() {
	// const NormalProgram normalProgram;
	// _programList.normalProgram = normalProgram;
}




}