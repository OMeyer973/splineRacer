#pragma once
#ifndef __GAME__HPP
#define __GAME__HPP

#include <iostream>
#include <string>
#include "json.hpp"
#include "common.hpp"
#include "Player.hpp"
#include "AssetManager.hpp"
#include "Camera.hpp"
#include "POVCamera.hpp"
#include "TrackballCamera.hpp"
#include "RenderManager.hpp"
#include "Obstacle.hpp"
#include "Collectable.hpp"

namespace splineengine {


/// \brief class wich represents the game scene , the player and their mechanics
class Game {
	// METHODS
	public:
		// CONSTRUCTORS - DESTRUCTORS
		/// \brief default constructor for infinite game
	    Game();

		/// \brief constructor with level name for loading level
	    Game(int levelId);

		/// \brief destructor
		~Game();

        // CONST GETTERS
		/// \brief get the player as a const ref
    const Player& player() const { return _player; }

    // NON-CONST GETTERS (can be used as setters)
    /// \brief get the player as a ref
    Player& player() { return _player; }


		//METHODS
		/// \brief creates a radom level
		void loadLevel();
		/// \brief load the given level
		void loadLevel(int levelId);

		/// \brief update called at each frame (for the physics)
		void update();

		/// \brief renders the scene at each frame
		void render();

		/// \brief rotate the camera in the horizontal direction by dx pixels
		void moveCameraX(const float dx);
		/// \brief rotate the camera in the vertical direction by dx pixels
		void moveCameraY(const float dy);
		/// \brief zoom the camera view  by a factor of dz
		void zoomCamera(const float dz);
		/// \brief switch between the different available cameras
		void changeCamera();

	private:
		GameObject gameObjFromJson(nlohmann::json j);


		// MEMBERS
		/// \brief manage the camera transformations
		RenderManager _renderManager;
		/// \brief vector of pointers on available cameras
		std::vector<std::unique_ptr<Camera>> _cameras;
		/// \brief id of the current camera
		int _chosenCamera;

		/// \brief represents the player
		Player _player;
		/// \brief represents the spline
    Spline _spline;

    std::vector<GameObject> _decorations;
    std::vector<Obstacle> _obstacles;
    std::vector<Collectable> _collectables;
		std::vector<GameObject> _skybox;
		// CONSTANTS
		std::string _playerModelName = "plane";

};

}
#endif
