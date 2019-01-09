#pragma once
#ifndef __GAMEMANAGER__HPP
#define __GAMEMANAGER__HPP

#include <iostream>
#include <unordered_set> 
#include <memory>
#include <GL/glew.h>
#include <glimac/SDLWindowManager.hpp>
#include <glimac/Plane.hpp>

#include "Settings.hpp"
#include "common.hpp"
#include "Game.hpp"
#include "Menu.hpp"
#include "Pause.hpp"

namespace splineengine {

// grouping keys by acion
struct KeyGroup {
	public:
		KeyGroup(std::unordered_set<SDLKey> keys)
			:_keys(keys)
		{};
		bool has(const SDLKey key) const { return _keys.find(key) != _keys.end(); }
	private: 
		std::unordered_set<SDLKey> _keys;
};

// keys and the actions they trigger
struct Input {
	typedef std::unordered_set<SDLKey> Keylist;
	public: // all public for ease of use but all const so no problem
		const KeyGroup up 				= KeyGroup(Keylist { SDLK_z, SDLK_UP } ); 
		const KeyGroup left 			= KeyGroup(Keylist { SDLK_q, SDLK_LEFT } ); 
		const KeyGroup down 			= KeyGroup(Keylist { SDLK_s, SDLK_DOWN } ); 
		const KeyGroup right 			= KeyGroup(Keylist { SDLK_d, SDLK_RIGHT } );
		const KeyGroup select 			= KeyGroup(Keylist { SDLK_RETURN, SDLK_SPACE } );
		const KeyGroup back 			= KeyGroup(Keylist { SDLK_ESCAPE, SDLK_BACKSPACE } );
		const KeyGroup togglePause 		= KeyGroup(Keylist { SDLK_ESCAPE, SDLK_p } );
		const KeyGroup cameraForward 	= KeyGroup(Keylist { SDLK_KP_PLUS, SDLK_PLUS } );
		const KeyGroup cameraBackward 	= KeyGroup(Keylist { SDLK_KP_MINUS, SDLK_MINUS } );
		const KeyGroup toggleCamera 	= KeyGroup(Keylist { SDLK_c } );
};

const Input input;
	
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
		/// \brief game screen where you play & have fun ! (ptr because it is destroyed between games)
		std::unique_ptr<Game> _game;
		/// \brief pause screen for when you need to go peepee
		Pause _pause;

		// id of the curently selected level
		std::string _levelName;

		/// \brief are we currently quitting the game ?
		bool _exiting;
		/// \brief wich is the active screen ? can be GAME, MENU, PAUSE (cf commons.hpp)
		int _activeScreen = MENU; // TODO : initialize at MENU for final version
};
}
#endif
