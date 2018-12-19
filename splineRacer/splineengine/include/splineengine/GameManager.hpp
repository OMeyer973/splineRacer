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

		// handle an event for all the screens
		void handleEvent(SDL_Event e);

		// CONST GETTERS
		/// \brief get the time difference in seconds between the current frame and the previous (enforced)
		float deltaTime() const { return _deltaTime; };

		/// \brief are we currently quitting the game ?
		const bool exiting() const { return _exiting; };

		/// \brief get the application path
		const glimac::FilePath& appPath() const { return _appPath; };

		// NON-CONST GETTERS (can be used as setters)
		/// \brief set the application path
		glimac::FilePath& appPath() { return _appPath; };
		
	private:

		/// \brief do the given event when in the MENU screen
		void doMenuEvent(SDL_Event e);
		/// \brief do the given event when in the GAME screen
		void doGameEvent(SDL_Event e);
		/// \brief do the given event when in the GAME screen
		void doPauseEvent(SDL_Event e);

		/// \brief init a new game.
		void initGame();
		/// \brief go to the game screen. init the game if necessary
		void goToGame();
		/// \brief go to the menu screen. reset the game
		void goToMenu();
		/// \brief go to the pause screen. pauses the game
		void goToPause();

		// MEMBERS
	
		// VARIABLES
		/// \brief menu screen with buttons & stuff
		Menu _menu;
		/// \brief game screen where you play & have fun !
		std::unique_ptr<Game> _game;
		/// \brief pause screen for when you need to go peepee
		Pause _pause;
		/// \brief path of the app
		glimac::FilePath _appPath;

		/// \brief are we currently quitting the game ?
		bool _exiting;
		/// \brief wich is the active screen ? can be GAME, MENU, PAUSE (cf commons.hpp)
		int _activeScreen = MENU; // TODO : initialize at MENU for final version

		// CONSTANTS
		static const uint32_t _windowWidth = 800;
		static const uint32_t _windowHeight = 600;
		/// \brief time between 2 frames (ms)
		static const Uint32 _framerate_ms = 1000 / 30;
		/// \brief time between 2 frames (seconds)
		const float _deltaTime = 1.f/30.f;
};
}
#endif