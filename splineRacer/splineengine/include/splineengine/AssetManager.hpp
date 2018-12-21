#pragma once
#ifndef __ASSETMANAGER__HPP
#define __ASSETMANAGER__HPP

#include <iostream>
#include <map>
#include "Model.hpp"

namespace splineengine {

// IDs of models
const int PLANEMODEL = 0;
const int WHEELBARROWMODEL = 1; 
const int SINGEMODEL = 2;

/// \brief class wich manages the assets for everyone to access them 
class AssetManager {
	// SINGLETON CONSTRUCTORS - DESTRUCTORS
	private:
		/// \brief private constructor
		AssetManager();
		// TODO : remove this comented code because probably useless
		// {
		// 	std::cout << "AssetManager constructor " << std::endl;
		// 	loadAssets();
		// };
		/// \brief private destructor
		~AssetManager()
		{};

	public:
		/// \brief access the singleton instance
		static AssetManager& instance() {
			static AssetManager instance;
			if (!instance._isLoaded) {
				instance.loadAssets();
			}
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
		
		// NON-CONST GETTERS
		std::map<int, Model>& models() { return _models; };
	
	private:
		// METHODS
		void loadAssets();

		// MEMBERS
		/// \brief have the assets been loaded allready ?
		bool _isLoaded;
		/// \brief 3D models assets
		std::map<int, Model> _models;

		//TODO : add this stuff
		
		/// \brief textures assets
		// std::map<int, Texture> _textures;
		/// \brief shader programs
		// std::map<int, Program> _programs;
};
}
#endif