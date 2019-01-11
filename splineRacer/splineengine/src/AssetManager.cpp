#include "splineengine/AssetManager.hpp"

namespace splineengine {

AssetManager::AssetManager()
{
	if (debug) std::cout << "AssetManager constructor " << std::endl;
	loadAssets();

	try {
		loadScores();
	}
	catch (const Error &e) {
		e.what();
	}

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
	_models.insert(std::make_pair("skybox",		Model("skybox")));
	_models.insert(std::make_pair("cloud",		Model("cloud")));
	_models.insert(std::make_pair("coin",		Model("coin")));
	_models.insert(std::make_pair("prism",		Model("sphere")));
	_models.insert(std::make_pair("frontmenu",	Model("frontmenu")));
	_models.insert(std::make_pair("menu",		Model("menu")));
	_models.insert(std::make_pair("alien",		Model("alien")));
	_models.insert(std::make_pair("finish_line",Model("finish_line")));
	_models.insert(std::make_pair("clouds",Model("clouds")));
	_models.insert(std::make_pair("tower",Model("tower")));
}

void AssetManager::loadScores() {
	if (debug) std::cout << "AssetManager : Load scores" << std::endl;

	std::string scorePath = Settings::instance().appPath().dirPath()
		+ ("../../splineRacer/assets/scores.json");

	if (debug) std::cout << "loading scores from file : " << scorePath << std::endl;

	// TODO : check for exception
	std::ifstream scoreStream(scorePath);
	if (scoreStream.fail()) {
		throw(Error("tried to read invalid score json file", __FILE__, __LINE__));
	}

	nlohmann::json scores;
	scoreStream >> scores;

	for (nlohmann::json::iterator it = scores.begin(); it != scores.end(); ++it) {
		_scores.insert(std::make_pair((*it)["name"].get<std::string>(), (*it)["score"]));
	}
}

void AssetManager::setupText() {
	_textManager.setupTTF();
}

void AssetManager::saveScores() {
	if (debug) std::cout << "AssetManager : Save scores" << std::endl;

	std::string scorePath = Settings::instance().appPath().dirPath()
		+ ("../../splineRacer/assets/scores.json");

	if (debug) std::cout << "saving scores to file : " << scorePath << std::endl;

	nlohmann::json baseObject;
	nlohmann::json object;
	for (std::map<std::string, int>::iterator it = _scores.begin(); it != _scores.end(); ++it) {
		object["name"] = it->first;
		object["score"] = it->second;
		baseObject.push_back(object);
		object.clear();
	}
	std::ofstream outFile(scorePath);
	outFile << std::setw(4) << baseObject << std::endl;
}



}
