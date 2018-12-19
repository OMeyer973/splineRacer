#pragma once
#ifndef __GAME__HPP
#define __GAME__HPP

#include "common.hpp"
#include "Player.hpp"

namespace splineengine {

/// \brief class wich represents the game scene , the player and their mechanics
class Game {
	// METHODS
	public:
		// CONSTRUCTORS - DESTRUCTORS
	    Game();

		/// \brief destructor
		~Game()
		{};

        // CONST GETTERS
		/// \brief get the player as a const ref
        const Player& player() const { return _player; }

        // NON-CONST GETTERS (can be used as setters)
        /// \brief get the player as a ref
        Player& player() { return _player; }


		//METHODS
		/// \brief init game when launching new game
		void init();

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




};
}
#endif