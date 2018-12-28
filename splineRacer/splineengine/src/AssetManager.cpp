#include "splineengine/AssetManager.hpp"

namespace splineengine {

AssetManager::AssetManager()
{
	std::cout << "AssetManager constructor " << std::endl;
	loadAssets();
	loadPrograms();
}

void AssetManager::loadAssets() {
	std::cout << "AssetManager : Load assets" << std::endl;
	
	// TODO : load actual assets for the game
	Model planeModel("plane");
	Model singeModel("singe");
	Model skyboxModel("skybox");
	Model wheelbarrowModel("wheelbarrow");
	_models.insert(std::make_pair(PLANEMODEL, planeModel));
	_models.insert(std::make_pair(WHEELBARROWMODEL, wheelbarrowModel));
	_models.insert(std::make_pair(SINGEMODEL, singeModel));
	_models.insert(std::make_pair(SKYBOXMODEL, skyboxModel));
}

void AssetManager::loadPrograms() {
	// const NormalProgram normalProgram;
	// _programList.normalProgram = normalProgram;
}




}