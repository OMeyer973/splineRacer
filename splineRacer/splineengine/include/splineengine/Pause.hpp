#pragma once
#ifndef __PAUSE__HPP
#define __PAUSE__HPP

#include "common.hpp"
#include <splineengine/Texture.hpp>
#include <splineengine/Model.hpp>

namespace splineengine {

/// \brief class wich represents the pause screen, the buttons and their actions
class Pause {
	// METHODS
	public:
		// CONSTRUCTORS - DESTRUCTORS
		/// \brief constructor
	    Pause();

		/// \brief destructor
		~Pause()
		{};


		//METHODS
		/// \brief init menu when launching the game
		void init();

		/// \brief update called at each frame
		void update();

		/// \brief  render the pause screen at each frame
		void render();

	// MEMBERS
	private:



};
}
#endif
