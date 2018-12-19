#pragma once
#ifndef __GAMEMANAGER__HPP
#define __GAMEMANAGER__HPP

#include <iostream>
#include <GL/glew.h>
#include <glimac/SDLWindowManager.hpp>
#include <splineengine/GameObject.hpp>

#include "common.hpp"
#include "Game.hpp"
#include "Menu.hpp"
#include "Pause.hpp"
#include "Player.hpp"

namespace splineengine {

/// \brief class wich manages the whole program 
// TODO: make it a singleton ! (it's hard)
class GameManager {
	// SINGLETON CONSTRUCTORS - DESTRUCTORS
	private:
		/// \brief private constructor
		GameManager();
		/// \brief private destructor
		~GameManager()
		{};

	public:

		/// \brief access the singleton instance
		static GameManager& instance() {
			static GameManager instance;
			return instance;
		}
		// prevent copy
		GameManager(const GameManager&) = delete;
	    GameManager(GameManager&&) = delete;
	    GameManager& operator=(const GameManager&) = delete;
	    GameManager& operator=(GameManager&&) = delete;

	public:
		//METHODS
		/// \brief init gamemanager when openning the software
		void init();

		/// \brief update is called at each frame
		void update();

		/// \brief exit the software
		void quit();

		// handle events for all the screens
		void handleEvent(SDL_Event e);
		// do the given event when in the MENU screen
		void doMenuEvent(SDL_Event e);
		// do the given event when in the GAME screen
		void doGameEvent(SDL_Event e);
		// do the given event when in the GAME screen
		void doPauseEvent(SDL_Event e);

		/// \brief get the time difference in seconds between the current frame and the previous (enforced)
		float deltaTime() const { return _deltaTime; };

		/// \brief are we currently quitting the game ?
		const bool exiting() const { return _exiting; };
		
	// MEMBERS
	private:

		// THE DIFFERENT SCREENS OF THE PROGRAM
		/// \brief menu screen with buttons & stuff
		Menu _menu;
		/// \brief game screen where you play & have fun !
		Game _game;
		/// \brief pause screen for when you need to go peepee
		Pause _pause;

		// MEMBERS THAT CAN BE GET & SET
		/// \brief are we currently quitting the game ?
		bool _exiting;
		/// \brief wich is the active screen ? can be GAME, MENU, PAUSE (cf commons.hpp)
		int _activeScreen = GAME; // TODO : initialize at MENU in for final version

		// PRIVATE CONST MEMBERS
		static const uint32_t _windowWidth = 800;
		static const uint32_t _windowHeight = 600;
		/// \brief time between 2 frames (ms)
		static const Uint32 _framerate_ms = 1000 / 30;
		/// \brief time between 2 frames (seconds)
		const float _deltaTime = 1.f/30.f;
};
}
#endif