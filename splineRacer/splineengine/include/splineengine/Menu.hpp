#pragma once
#ifndef __MENU__HPP
#define __MENU__HPP

#include <iostream>
#include <string>
#include "common.hpp"
#include "AssetManager.hpp"
#include "Player.hpp"
#include "RenderManager.hpp"
#include "Camera.hpp"
#include "POVCamera.hpp"
#include "TrackballCamera.hpp"

namespace splineengine {

/// \brief class wich represents the menu, the buttons and their actions
class Menu {
	// METHODS
	public:
		// CONSTRUCTORS - DESTRUCTORS
		/// \brief constructor
	    Menu();

		/// \brief destructor
		~Menu();


		//METHODS
		/// \brief init menu when launching the game
		void init();

		/// \brief update called at each frame
		void update();

		/// \brief render the menu at each frame
		void render();


		void moveCameraX(const float dx);

		void changePannel(const int pannelState);

		/// \brief select the next or previous level
		/// \param lvlUpOrDown == + or - 1
		void changeLevel(const int lvlUpOrDown);

		void rotateHorizontally(const float dx);

		void rotateVertically(const float dx);

		/// \brief activate the display of the level
		void displayLevels() { _displayLevels = true; }
		/// \brief deactivate the display of the level
		void hideLevels() { _displayLevels = false; }

		bool isDisplayingLevels() { return _displayLevels; }

		/// \brief return the name of the currently selected menu
		std::string selectedMenu() { return _menus[abs(_selectedMenu % 6)]; }

		/// \brief return the name of the currently selected level
		std::string selectedLevel() { return _levels[_selectedLevel]; }

		bool isRotatingHorizontally() { return _isRotatingHorizontally; }
		bool isRotatingVertically() { return _isRotatingVertically; }

	// MEMBERS
	private:
		RenderManager _renderManager;
		/// \brief vector of pointers on available cameras
		std::vector<std::unique_ptr<Camera>> _cameras;
		/// \brief id of the current camera
		int _chosenCamera;

		bool _isRotatingHorizontally;
		bool _isRotatingVertically;

		bool _displayLevels;

		int _rotationDirection;
		int _rotationAngle;
		int _tickVertical;

		Player _player;
	  	std::vector<GameObject> _menuItems;
		std::vector<GameObject> _skybox;
		std::string _frontMenuModelName = "frontmenu";

		int _selectedMenu;
		int _selectedLevel;
		std::vector<std::string> _menus = { "Play","Scores","Settings","Rules","Credits","Quit"};
		std::vector<std::string> _levels = { "Easy", "Normal","Hard","Infinite" };


};
}
#endif
