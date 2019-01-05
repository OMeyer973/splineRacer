#pragma once
#ifndef __SETTINGS__HPP
#define __SETTINGS__HPP

#include "common.hpp"
#include <glimac/FilePath.hpp>
#include <SDL/SDL.h>

namespace splineengine {

/// \brief class wich represents the Settings
class Settings {
	// SINGLETON CONSTRUCTORS - DESTRUCTORS
	private:
		/// \brief private constructor
		Settings() {};
		/// \brief private destructor
		~Settings() {};

	public:
		/// \brief access the singleton instance
		static Settings& instance() {
			static Settings instance;
			return instance;
		}
		// prevent copy
		Settings(const Settings&) = delete;
	    Settings(Settings&&) = delete;
	    Settings& operator=(const Settings&) = delete;
	    Settings& operator=(Settings&&) = delete;

		// CONST GETTERS
		/// \brief get the time difference in seconds between the current frame and the previous (enforced)
		float deltaTime() const { return _deltaTime; };
		/// \brief get the current time since the application is running
		float time() const { return _time; };

		/// \brief get the application path
		const glimac::FilePath& appPath() const { return _appPath; };
		
		/// \brief get the frame rate
		const Uint32 framerate() const { return _framerate_ms; };

		// NON-CONST GETTERS (can be used as setters)
		/// \brief set the application path
		glimac::FilePath& appPath() { return _appPath; };
		
		// METHODS
		/// \brief updates the current time at each frame
		void updateTime() { _time += _deltaTime; };

	// MEMBERS
	private:
		// CONSTANTS
		/// \brief path of the app
		glimac::FilePath _appPath;
		const uint32_t _windowWidth = 800;
		const uint32_t _windowHeight = 600;
		/// \brief time between 2 frames (ms)
		const Uint32 _framerate_ms = 1000 / 30;
		/// \brief time between 2 frames (seconds)
		const float _deltaTime = 1.f/30.f;
		float _time = 0.f;



};
}
#endif