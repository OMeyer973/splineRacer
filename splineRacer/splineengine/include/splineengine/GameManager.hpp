#pragma once
#ifndef __GAMEMANAGER__HPP
#define __GAMEMANAGER__HPP

#include <GL/glew.h>
#include "common.hpp"

namespace splineengine {

/// \brief represents a object in the game, with a position and a set of colliders
class GameManager {
	// METHODS
	public:
		// CONSTRUCTORS - DESTRUCTORS
	    /// \brief default constructor (position(0.f,0.f,0.f), no colliders)
		GameManager()
			:_time(SDL_GetTicks()), _prevTime(SDL_GetTicks())
		{};

		/// \brief destructor
		~GameManager()
		{};

		//CONST GETTERS
		/// \brief get the time of the current frame as a const
		const float time() const { return _time; }

		//METHODS
		/// \brief get the current time in seconds
		void update() {
 		   _prevTime = _time;
 		   _time = 0.001f * SDL_GetTicks();
		};

		/// \brief get the time difference in seconds between the current frame and the previous (enforced)
		float fixedDtime() const { return _fixedDTime; };
		
		/// \brief get the time difference in seconds between the current frame and the previous
		// not useful when framerate is varying too much
		float dtime() const {
			return _time - _prevTime;
		};

	// MEMBERS
	protected:
		// \brief time of the current frame (in sec)
		float _time;
		// \brief time of the previous frame (in sec)
		float _prevTime;
		/// \brief fixed timestep 
		float _fixedDTime = 1.f/60;
};
}
#endif