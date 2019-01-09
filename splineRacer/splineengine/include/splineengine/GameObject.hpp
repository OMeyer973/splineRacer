#pragma once
#ifndef __GAMEOBJECT__HPP
#define __GAMEOBJECT__HPP

#include <iostream>
#include "common.hpp"
#include <splineengine/Spline.hpp>
#include <splineengine/Model.hpp>
#include <splineengine/common.hpp>
#include <splineengine/AssetManager.hpp>

namespace splineengine {

/// \brief ids of the gameobject animations and their parameters
const uint ROT_CONST_FWD = 0;
const uint ROT_CONST_LEFT = 1;
const uint ROT_CONST_UP = 2;

const uint MOVE_SIN_LEFT = 3;
const uint MOVE_SIN_UP = 4;

const uint MOVE_CONST_LEFT = 5;
const uint MOVE_CONST_RIGHT = 6;
const uint MOVE_CONST_BACK = 7;
const uint MOVE_CONST_FWD = 8;
const uint SCALE_SIN = 9;
typedef std::vector<uint> AnimationList;

const float rotConstSpeed = 3.f;
const float moveSinFreq = 0.5f;
const float moveSinAmp = 5.f;
const float moveConstSpeed = 1.f;
const float scaleSinAmp = 2.f;
const float scaleSinFreq = 0.5f;
const float moveSinAdjustedAmp = moveSinAmp / moveSinFreq;
const float scaleSinAdjustedAmp = scaleSinAmp / scaleSinFreq;
// factor taken into account when creating the animation seed from objecr fwd position
const float animationSeedFactor = 0.5f;


/// \brief transformation of an object (only used to simplfy gameObject constructor)
struct Transform {
	public: //all public for ease of use but const so no problem
		const glm::vec3& _sPosition = glm::vec3(0);
		const glm::vec3& _scale = glm::vec3(1);
		const glm::vec3& _rotation = glm::vec3(0);
		Transform(
			const glm::vec3& sPosition = glm::vec3(0),
			const glm::vec3& scale = glm::vec3(1),
			const glm::vec3& rotation = glm::vec3(0)
		):_sPosition(sPosition), _scale(scale), _rotation(rotation)
		{};
};

/// \brief represents a object in the game, with a position and a set of colliders
class GameObject {
	// METHODS
	public:
		// CONSTRUCTORS - DESTRUCTORS

		/// \brief constructor from parameters
		/// \param model 	: model of the obj
		/// \param spline 	: Spline spline reference for the object position
		/// \param isStatic : is the object unmovable ?
		/// \param position : glm::vec3 position of the object (relative to the spline)
		/// \param scale 	: glm::vec3 scale    of the object
		/// \param rotation : glm::vec3 rotation of the object
		GameObject (
			const Model& model,
			const Spline& spline,
			const std::string& textureName = "default.png",
			const bool isStatic = false,
			const Transform& transform = Transform(),
			//const uint animId = 0
			const AnimationList& animations = {}
		);

		/// \brief copy constructor
		/// \param g : GameObject to copy from
		GameObject(const GameObject& g);

		/// \brief operators
		// GameObject& operator=(const GameObject& g) {
		// 	_model	   = g._model;
		// 	_sPosition = g._sPosition;
		// 	_scale	   = g._scale;
		// 	_rotation  = g._rotation;
		// 	_isStatic  = g._isStatic;
		// 	_hasMatrix = false;
		// };


		/// \brief destructor
		virtual ~GameObject()
		{};


        // METHODS
		/// \brief returns the transform matrix of the object in it's spline reference
		const glm::mat4 matrix();
		/// \brief returns the transform matrix of the object reference
		const glm::mat4 staticMatrix();

		/// \brief update the object physics for the current frame
		void update();
		void addAnimation(uint animId);
		/// \brief Draw object
		void draw() const;

		/// \brief is the gameobject intersecting another gameobject ?
		bool intersect(GameObject& other);

		/// \brief [virtual function] trigger collision behavior when colliding with another Gameobjects.
		/// \brief needs to be implemented for classes inheriting from GameObject
		virtual void doCollisionWith(GameObject& other) {};

		/// \brief check if the gameobject intersects the other gameObject and trigger their collision behavior
		void collideWith(GameObject& other);

		//CONST GETTERS
		/// \brief Get the position of the object (relative to the spline) as a const reference
		const glm::vec3& sPosition() const { return _sPosition; }

		/// \brief Get the rotation of the object as aconst reference
		const glm::vec3& rotation() const { return _rotation; }

		/// \brief Get the scale of the object as a const reference
		const glm::vec3& scale() const { return _scale; }

		/// \brief Get the model of the object as a const reference
		const Model& model() const { return _model; }

		/// \brief is the object static ? (const ref)
		const bool& isStatic() const { return _isStatic; }


		// NON-CONST GETTERS (can be used as setters)
		/// \brief Get the position of the object (relative to the spline) as a reference
		glm::vec3& sPosition() { return _sPosition; }

		/// \brief Get the rotation of the object as a reference
		glm::vec3& rotation() { return _rotation; }

		/// \brief Get the scale of the object as a reference
		glm::vec3& scale() { return _scale; }

		/// \brief Get the model of the object as a reference
		Model model() { return _model;}

		void setTexture(const std::string textureName);

		/// \brief get Texture ID
		const GLuint textureID() const { return _textureID; };

	// MEMBERS
	protected:
		/// \brief 3D model of the object
		//std::unique_ptr<Model> _model; // better to use ptr because you can't reassign refs ?
		const Model& _model; // better to use refs because less mistakes ?

		/// \brief is the object unmovable ?
		const bool _isStatic = false;
		/// \brief spline reference for the object placement
		const Spline& _spline;

		/// \brief position of the object relative to the spline
		glm::vec3 _sPosition;
		/// \brief scale of the object
		glm::vec3 _scale;
		/// \brief rotation of the object folowing the 3 spline-reference vectors (fwd, left, up) in trigonometric rotation direction
		glm::vec3 _rotation;

		AnimationList _animations;
		/// \brief a seed to start certain animations (will use the original sPosition[FWD] of the object)

		/// \brief type of the gameObject : PLAYER, OBSTACLE, BONUS ...
		// (USELESS : just overload function that would need it with the class you want)
		// int _type;

		/// \brief stored transformation matrix of the object in case the object is static
		bool _hasMatrix = false;
		glm::mat4 _transformMat;

		/// \brief Texture ID of the model
		GLuint _textureID;

};

}

#endif
