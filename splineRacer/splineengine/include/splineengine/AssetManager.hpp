#pragma once
#ifndef __ASSETMANAGER__HPP
#define __ASSETMANAGER__HPP

#include <iostream>
#include <map>
#include <SDL/SDL.h>
#include <splineengine/GLSLProgram.hpp>
#include <splineengine/TextManager.hpp>
#include <splineengine/Model.hpp>
#include <splineengine/Texture.hpp>
#include <splineengine/json.hpp>

namespace splineengine {

/// \brief singleton class wich manages the assets for everyone to access them
class AssetManager {
	// SINGLETON CONSTRUCTORS - DESTRUCTORS
	private:
		/// \brief private constructor
		AssetManager();

		/// \brief private destructor
		~AssetManager()
		{
			saveScores();
		};

	public:
		/// \brief access the singleton instance
		static AssetManager& instance() {
			static AssetManager instance;
			return instance;
		}
		// prevent copy
		AssetManager(const AssetManager&) = delete;
		AssetManager(AssetManager&&) = delete;
		AssetManager& operator=(const AssetManager&) = delete;
		AssetManager& operator=(AssetManager&&) = delete;

	public:
		// CONST GETTERS
		const std::map<std::string, Model>& models() const { return _models; };

		const std::map<std::string, Texture>& textures() const { return _textures; };

		const std::map<std::string, int>& scores() const { return _scores; };

		const ProgramList& programList() { return _programList; };

		TextManager& textManager() { return _textManager; };

		// NON-CONST GETTERS
		std::map<std::string, Model>& models() { return _models; };

		std::map<std::string, Texture>& textures(){return _textures;};

		std::map<std::string, int>& scores(){return _scores;};

		void setupText();

		void saveScores();

	private:
		// METHODS
		/// \brief load assets
		void loadAssets();

		/// \brief load scores
		void loadScores();

		// MEMBERS
		/// \brief 3D models assets
		std::map<std::string, Model> _models;

		/// \brief Textures
		std::map<std::string, Texture> _textures;

		/// \brief Scores
		std::map<std::string, int> _scores;

		//TODO : add this stuff
		// std::map<int, Program> _programs;
		/// \brief shader programs

		/// \brief Program List
		const ProgramList _programList;

		/// \brief Text Manager
		TextManager _textManager;
		SDL_Joystick *_joystick;
};

}

#endif
