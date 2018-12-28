#pragma once
#ifndef __GAMEMANAGER__HPP
#define __GAMEMANAGER__HPP

#include <iostream>
#include <memory>
#include <GL/glew.h>
#include <glimac/SDLWindowManager.hpp>


#include "Settings.hpp"
#include "common.hpp"
#include "Game.hpp"
#include "Menu.hpp"
#include "Pause.hpp"

namespace splineengine {
	
// IDs of game screens
const int MENU = 0;
const int GAME = 1; 
const int PAUSE = 2;

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
		// CONST GETTERS

		/// \brief are we currently quitting the game ?
		const bool exiting() const { return _exiting; };

		//METHODS
		/// \brief init gamemanager when openning the software
		void init();

		/// \brief update is called at each frame
		void update();

		/// \brief exit the software
		void quit();

		// handle an event for all the screens
		void handleEvent(SDL_Event e);
		
	private:
		/// \brief do the given event when in the MENU screen
		void doMenuEvent(SDL_Event e);
		/// \brief do the given event when in the GAME screen
		void doGameEvent(SDL_Event e);
		/// \brief do the given event when in the GAME screen
		void doPauseEvent(SDL_Event e);

		/// \brief init a new game form a level id
		void initGame(const uint levelId);
		/// \brief init an infinite
		void initGame();
		/// \brief go to the game screen. init the game if necessary
		void goToGame();
		/// \brief go to the menu screen. reset the game
		void goToMenu();
		/// \brief go to the pause screen. pauses the game
		void goToPause();

		// MEMBERS
		/// \brief menu screen with buttons & stuff
		Menu _menu;
		/// \brief game screen where you play & have fun !
		std::unique_ptr<Game> _game;
		/// \brief pause screen for when you need to go peepee
		Pause _pause;

		// id of the curently selected level
		int _levelId = LEVEL_ENDLESS;

		/// \brief are we currently quitting the game ?
		bool _exiting;
		/// \brief wich is the active screen ? can be GAME, MENU, PAUSE (cf commons.hpp)
		int _activeScreen = MENU; // TODO : initialize at MENU for final version
};
}
#endif