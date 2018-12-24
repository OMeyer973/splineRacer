#pragma once
#ifndef __RENDER__MANAGER__HPP
#define __RENDER__MANAGER__HPP

#include <iostream>
#include <glimac/SDLWindowManager.hpp>
#include <splineengine/Camera.hpp>
#include <splineengine/Texture.hpp>
#include <splineengine/CubeMap.hpp>
#include <splineengine/GLSLProgram.hpp>

namespace splineengine {

/// \brief represents a object in the game, with a position and a set of colliders
class RenderManager {
	// METHODS
	public:
		// CONSTRUCTORS - DESTRUCTORS

		/// \brief Default constructor
		RenderManager()
		{};

		RenderManager(Camera &camera) {
			std::cout << "rendermanager construction from camera : " << std::endl
			<< "	setting projMatrix, MVMatrix, normalMatrix" << std::endl;
			// TODO : get resolution from settings instead of hard coded 800x600
			_projMatrix = glm::perspective(glm::radians(70.f), 800 / 600.f, 0.1f, 200.f);
			_MVMatrix = glm::translate(camera.getViewMatrix(), -5.f*fwdVec);
			_normalMatrix = glm::transpose(glm::inverse(_MVMatrix));
			std::cout << "done." << std::endl;
		};

		/// \brief Destructor
		~RenderManager()
		{};

		/// \brief Update _MVMatrix and _normalMatrix
		void updateMVMatrix(Camera &camera, glm::mat4 transformMatrix);

		/// \brief get _MVMatrix
		glm::mat4 MVMatrix() const {
			return _MVMatrix;
		}

		/// \brief get _normalMatrix
		glm::mat4 normalMatrix() const {
			return _normalMatrix;
		}

		/// \brief get _projMatrix
		glm::mat4 projMatrix() const {
			return _projMatrix;
		}

		/// \brief Use the correct program associated to the shader
		void useProgram(FS shader);

		/// \brief Apply Transformations, Update Uniforms
		void applyTransformations(FS shader, glm::mat4 matrix);

	// MEMBERS
	protected:
		/// \brief Projection matrix
		glm::mat4 _projMatrix;
		/// \brief Model-View matrix
		glm::mat4 _MVMatrix;
		/// \brief Model-View matrix
		glm::mat4 _normalMatrix;

		CubeMap* _skybox;

};

}

#endif
