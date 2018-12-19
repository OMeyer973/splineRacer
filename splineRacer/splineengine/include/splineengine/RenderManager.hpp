#pragma once
#ifndef __RENDER__MANAGER__HPP
#define __RENDER__MANAGER__HPP

#include <glimac/SDLWindowManager.hpp>
#include <splineengine/Camera.hpp>
#include <splineengine/Texture.hpp>
#include <iostream>
#include <vector>

namespace splineengine {

/// \brief represents a object in the game, with a position and a set of colliders
class RenderManager {
	// METHODS
	public:
		// CONSTRUCTORS - DESTRUCTORS

		/// \brief Default constructor
		RenderManager(Camera &camera) {
			_projMatrix = glm::perspective(glm::radians(70.f), 800 / 600.f, 0.1f, 100.f);
			_MVMatrix = glm::translate(camera.getViewMatrix(), glm::vec3(0, 0, -5));
			_normalMatrix = glm::transpose(glm::inverse(_MVMatrix));
		};

		/// \brief destructor
		~RenderManager()
		{};

		/// \brief Update _MVMatrix and _normalMatrix
		void updateMVMatrix(Camera &camera, glm::mat4 transformMatrix);
		
		/// \brief get _MVMatrix
		glm::mat4 MVMatrix() {
			return _MVMatrix;
		}

		/// \brief get _normalMatrix
		glm::mat4 normalMatrix() {
			return _normalMatrix;
		}

		/// \brief get _projMatrix
		glm::mat4 projMatrix() {
			return _projMatrix;
		}


	// MEMBERS
	protected:
		/// \brief Projection matrix
		glm::mat4 _projMatrix;
		/// \brief Model-View matrix
		glm::mat4 _MVMatrix;
		/// \brief Model-View matrix
		glm::mat4 _normalMatrix;
		std::vector<Texture> _textures;

};

}

#endif