#pragma once
#ifndef __MENU__HPP
#define __MENU__HPP

#include "common.hpp"

namespace splineengine {

/// \brief class wich represents the menu, the buttons and their actions
class Menu {
	// METHODS
	public:
		// CONSTRUCTORS - DESTRUCTORS
		/// \brief constructor
	    Menu();

		/// \brief destructor
		~Menu()
		{};

		
		//METHODS
		/// \brief init menu when launching the game
		void init();

		/// \brief update called at each frame
		void update();

		/// \brief render the menu at each frame
		void render();
		
	// MEMBERS
	private:



};
}
#endif