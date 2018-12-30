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
		{
			_projMatrix = glm::perspective(glm::radians(70.f), 800 / 600.f, 0.1f, 200.f);
			_skybox = new CubeMap(
				"../../../assets/textures/posx.png",
				"../../../assets/textures/negx.png",
				"../../../assets/textures/posy.png",
				"../../../assets/textures/negy.png",
				"../../../assets/textures/posz.png",
				"../../../assets/textures/negz.png"
			);
		};

		RenderManager(Camera &camera) {
			if (debug) std::cout << "rendermanager construction from camera : " << std::endl
			<< "	setting projMatrix, MVMatrix, normalMatrix" << std::endl;
			// TODO : get resolution from settings instead of hard coded 800x600
			_projMatrix = glm::perspective(glm::radians(70.f), 800 / 600.f, 0.1f, 200.f);
			_MVMatrix = glm::translate(camera.getViewMatrix(), -5.f*fwdVec);
			_normalMatrix = glm::transpose(glm::inverse(_MVMatrix));
			if (debug) std::cout << "done." << std::endl;
		};

		/// \brief Destructor
		~RenderManager()
		{};

		/// \brief Update _MVMatrix and _normalMatrix
		void updateMVMatrix(Camera &camera, glm::mat4 transformMatrix);

		/// \brief Update _globalMatrix
		void updateGlobalMatrix(Camera &camera, glm::mat4 splineCamMatrix);

		/// \brief get _MVMatrix
		const glm::mat4 MVMatrix() const {
			return _MVMatrix;
		}

		/// \brief get _normalMatrix
		const glm::mat4 normalMatrix() const {
			return _normalMatrix;
		}

		/// \brief get _projMatrix
		const glm::mat4 projMatrix() const {
			return _projMatrix;
		}

		/// \brief Use the correct program associated to the shader
		void useProgram(FS shader);

		/// \brief Apply Transformations, Update Uniforms
		void applyTransformations(FS shader);

	// MEMBERS
	protected:
		/// \brief Projection matrix
		glm::mat4 _projMatrix;
		/// \brief Model-View matrix
		glm::mat4 _MVMatrix;
		/// \brief Model-View matrix
		glm::mat4 _normalMatrix;
		/// \brief Global matrix
		glm::mat4 _globalMatrix;

		CubeMap* _skybox;

};

}

#endif
