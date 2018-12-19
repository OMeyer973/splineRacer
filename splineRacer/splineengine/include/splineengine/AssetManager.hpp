#pragma once
#ifndef __ASSETMANAGER__HPP
#define __ASSETMANAGER__HPP

#include <iostream>
#include "Model.hpp"

namespace splineengine {

/// \brief class wich manages the assets for everyone to access them 
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
		
	private:
		std::vector<Model> _models;
};
}
#endif