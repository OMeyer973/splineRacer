#pragma once
#ifndef __ASSETMANAGER__HPP
#define __ASSETMANAGER__HPP

#include <iostream>
#include <map>
#include <splineengine/GLSLProgram.hpp>
#include <splineengine/TextManager.hpp>
#include <splineengine/Model.hpp>
#include <splineengine/Texture.hpp>

namespace splineengine {

/// \brief singleton class wich manages the assets for everyone to access them
class AssetManager {
	// SINGLETON CONSTRUCTORS - DESTRUCTORS
	private:
		/// \brief private constructor
		AssetManager();

		/// \brief private destructor
		~AssetManager()
		{};

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

		//const std::map<std::string, Texture>& textures() const { return _textures; };

		const ProgramList& programList() { return _programList; };

		TextManager& textManager() { return _textManager; };

		// NON-CONST GETTERS
		std::map<std::string, Model>& models() { return _models; };

		std::map<std::string, Texture>& textures(){return _textures;};

		void setupText();




	private:
		// METHODS
		void loadAssets();


		// MEMBERS
		/// \brief 3D models assets
		std::map<std::string, Model> _models;

		std::map<std::string, Texture> _textures;

		//TODO : add this stuff

		/// \brief textures assets
		// std::map<int, Texture> _textures;
		/// \brief shader programs
		// std::map<int, Program> _programs;

		/// \brief Program List
		const ProgramList _programList;

		/// \brief Text Manager
		TextManager _textManager;
};

}

#endif
