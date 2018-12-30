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

		void moveToPannel(const float dx);

		bool isRotating() { return _isRotating;}
	// MEMBERS
	private:
		RenderManager _renderManager;
		/// \brief vector of pointers on available cameras
		std::vector<std::unique_ptr<Camera>> _cameras;
		/// \brief id of the current camera
		int _chosenCamera;

		bool _isRotating;
		Player _player;

    std::vector<GameObject> _menuItems;
		std::vector<GameObject> _skybox;

		std::string _frontMenuModelName = "frontmenu";


};
}
#endif
