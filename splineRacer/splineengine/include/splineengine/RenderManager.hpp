#pragma once
#ifndef __RENDER__MANAGER__HPP
#define __RENDER__MANAGER__HPP

#include <iostream>
#include <glimac/Program.hpp>
#include <glimac/SDLWindowManager.hpp>
#include <splineengine/Camera.hpp>
#include <splineengine/Texture.hpp>
#include <splineengine/CubeMap.hpp>
#include <splineengine/GameObject.hpp>
#include <splineengine/GLSLProgram.hpp>
#include <splineengine/Light.hpp>
#include <splineengine/AssetManager.hpp>

namespace splineengine {

// forward declaration
class GameObject;

/// \brief This class is used to handle shader choice and matrices calculations
class RenderManager {
	// METHODS
	public:
		// CONSTRUCTORS - DESTRUCTORS

		/// \brief Default constructor
		RenderManager() {
			_projMatrix = glm::perspective(glm::radians(70.f), 800 / 600.f, 0.1f, 200.f);
			_lightsCount = 0;
		};

		RenderManager(Camera &camera) {
			if (debug) std::cout << "rendermanager construction from camera : " << std::endl
			<< "	setting projMatrix, MVMatrix, normalMatrix" << std::endl;
			// TODO : get resolution from settings instead of hard coded 800x600
			_projMatrix = glm::perspective(glm::radians(70.f), 800 / 600.f, 0.1f, 200.f);
			_MVMatrix = glm::translate(camera.getViewMatrix(), -5.f*fwdVec);
			_normalMatrix = glm::transpose(glm::inverse(_MVMatrix));
			_globalMatrix = _MVMatrix;

			_lightsCount = 0;
			_textColor = glm::vec3(1.f, 1.f, 1.f);
			_enableGlBlend = false;

			if (debug) std::cout << "done." << std::endl;
		};

		/// \brief Destructor
		~RenderManager()
		{};

		/// \brief Update _MVMatrix and _normalMatrix
		void updateMVMatrix(Camera &camera, glm::mat4 transformMatrix, glm::vec3 scale);

		/// \brief Update _globalMatrix
		void updateGlobalMatrix();


		// CONST GETTERS
		/// \brief get _MVMatrix
		const glm::mat4& MVMatrix() const {
			return _MVMatrix;
		}

		/// \brief get _normalMatrix
		const glm::mat4& normalMatrix() const {
			return _normalMatrix;
		}

		/// \brief get _projMatrix
		const glm::mat4& projMatrix() const {
			return _projMatrix;
		}

		/// \brief get _splineCamMatrix
		const glm::mat4& splineCamMatrix() const {
			return _splineCamMatrix;
		}

		/// \brief get _splineCamMatrix
		const unsigned int& lightsCount() const {
			return _lightsCount;
		}

		// NON CONST GETTERS (to use as setters)
		/// \brief get _splineCamMatrix
		glm::mat4& splineCamMatrix() {
			return _splineCamMatrix;
		}

		/// \brief Use the correct program associated to the shader
		void useProgram(FS shader);

		/// \brief Apply Transformations, Update Uniforms
		void sendUniformsToShaders(FS shader);

		/// \brief Calculate Matrix and draw object
		void drawObject(GameObject& obj, Camera& camera);

		/// \brief Init Menu lights
		void initMenuLights();

		/// \brief Init Game lights
		void initGameLights();

		/// \brief Update menu lights position and direction
		void updateMenuLights();

		/// \brief Update ingame light position and direction
		void updateGameLights();

		/// \brief Add a light to the render manager
		void addLight(const bool isPoint,
					  const glm::vec3 &posOrDir,
					  const glm::vec3 &Kd,
					  const glm::vec3 &Ks,
					  const float &shininess,
					  const glm::vec3 &lightIntensity);

		/// \brief Update Light position and direction
		void clearLights();

		/// \brief Draw distance to alien
		void drawDistanceToAlien(const float distance);

		/// \brief Draw score
		void drawScore(const unsigned int score);

		/// \brief Draw win Card
		void drawWinCard();

		/// \brief Draw lose Card
		void drawLoseCard();

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

		/// \brief Spline cam matrix
		glm::mat4 _splineCamMatrix;

		/// \brief Skybox
		CubeMap* _skybox;

		/// \brief Lights
		std::vector<Light> _lights;

		/// \brief Lights count
		unsigned int _lightsCount;

		/// \brief Text color
		glm::vec3 _textColor;

		/// \brief Enable GL_BLEND ?
		bool _enableGlBlend;

};

}

#endif
