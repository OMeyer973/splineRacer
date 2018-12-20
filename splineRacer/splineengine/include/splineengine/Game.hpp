#pragma once
#ifndef __GAME__HPP
#define __GAME__HPP

#include <iostream>
#include <string>
#include <string>
#include "common.hpp"
#include "Player.hpp"
#include "AssetManager.hpp"

namespace splineengine {

/// \brief class wich represents the game scene , the player and their mechanics
class Game {
	// METHODS
	public:
		// CONSTRUCTORS - DESTRUCTORS
		/// \brief default constructor for infinite game
	    Game();

		/// \brief constructor with level name for loading level
	    Game(std::string levelName);

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
		void loadLevel(std::string levelName);

		/// \brief update called at each frame (for the physics)
		void update();

		/// \brief renders the scene at each frame
		void render();
		
	// MEMBERS
	private:
		/// \brief represents the player
		Player _player;
		/// \brief represents the spline
	    Spline _spline;

	    std::vector<GameObject> decorations;
	    std::vector<GameObject> obstacles;
	    std::vector<GameObject> collectables;
		// CONSTANTS
		std::string _playerModelName = "plane";



};
}
#endif