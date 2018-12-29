#pragma once
#ifndef __GAMEOBJECT__HPP
#define __GAMEOBJECT__HPP

#include <iostream>
#include "common.hpp"
#include "Model.hpp"
#include "Spline.hpp"

namespace splineengine {

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
			const bool isStatic = false,
			const glm::vec3& sPosition = glm::vec3(0),
			const glm::vec3& scale = glm::vec3(1),
			const glm::vec3& rotation = glm::vec3(0)
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
		const Model& model() { return _model; }

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

		/// \brief type of the gameObject : PLAYER, OBSTACLE, BONUS ... 
		// (USELESS : just overload function that would need it with the class you want)
		// int _type;

		/// \brief stored transformation matrix of the object in case the object is static
		bool _hasMatrix = false;
		glm::mat4 _transformMat;

};

}

#endif