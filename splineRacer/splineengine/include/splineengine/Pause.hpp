#pragma once
#ifndef __PAUSE__HPP
#define __PAUSE__HPP


#include <splineengine/common.hpp>
#include <splineengine/Texture.hpp>
#include <splineengine/Model.hpp>
#include <splineengine/AssetManager.hpp>
#include <splineengine/Camera.hpp>
#include <splineengine/POVCamera.hpp>
#include <splineengine/TrackballCamera.hpp>
#include <splineengine/Player.hpp>


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
		/// \brief move selectors
		void moveSelectors(float dy);

		/// \brief get current selected MENU
		std::string getPauseMenu(){return _pauseArray[_selectedMenu];};

	// MEMBERS
	private:
		RenderManager _renderManager;
		/// \brief vector of pointers on available cameras
		std::vector<std::unique_ptr<Camera>> _cameras;
		/// \brief id of the current camera
		int _chosenCamera;

		int _selectedMenu;
		float _movementDirection;

		bool _isMoving;

		int _tickVertical;

		std::vector<GameObject> _pauseItems;
		std::vector<GameObject> _selectors;
		std::vector<std::string> _pauseArray = {"QuitToMenu","Continue"};

};
}
#endif
