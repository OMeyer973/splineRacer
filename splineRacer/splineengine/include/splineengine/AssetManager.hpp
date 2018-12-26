#pragma once
#ifndef __ASSETMANAGER__HPP
#define __ASSETMANAGER__HPP

#include <iostream>
#include <map>
#include "Model.hpp"
#include <splineengine/GLSLProgram.hpp>

namespace splineengine {

// IDs of models
const int PLANEMODEL = 0;
const int WHEELBARROWMODEL = 1; 
const int SINGEMODEL = 2;
const int SKYBOXMODEL = 3;

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
		const std::map<int, Model>& models() const { return _models; };

		const ProgramList& programList() { return _programList; };
		
		// NON-CONST GETTERS
		std::map<int, Model>& models() { return _models; };

	private:
		// METHODS
		void loadAssets();
		void loadPrograms();

		// MEMBERS
		/// \brief 3D models assets
		std::map<int, Model> _models;

		//TODO : add this stuff
		
		/// \brief textures assets
		// std::map<int, Texture> _textures;
		/// \brief shader programs
		// std::map<int, Program> _programs;

		/// \brief Program List
		const ProgramList _programList;
};

}

#endif