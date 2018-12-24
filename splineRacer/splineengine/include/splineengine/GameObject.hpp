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
		/// \param position : Model model of the obj
		/// \param position : glm::vec3 position of the object (relative to the spline)
		/// \param position : glm::vec3 scale    of the object 
		/// \param position : glm::vec3 rotation of the object 
		// TDOO : add isStatic to constructio params ?
		GameObject (
			const Model& model = Model(),
			const glm::vec3& sPosition = glm::vec3(0),
			const glm::vec3& scale = glm::vec3(1),
			const glm::vec3& rotation = glm::vec3(0)
		)
			:
			_model(model),
			_sPosition(sPosition),
			_scale(scale),
			_rotation(rotation)
		{
			// std::cout << "GameObject constructor " << std::endl;
		};

		/// \brief copy constructor
		/// \param g : GameObject to copy from
		GameObject(const GameObject& g)
			:_model(g._model),
			_sPosition(g._sPosition),
			_scale(g._scale), 
			_rotation(g._rotation)
		{};
		
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
		~GameObject()
		{};


        // METHODS
		/// \brief returns the transform matrix of the object in the given spline reference
		const glm::mat4 matrix(const Spline& spline);
		
		/// \brief returns the transform matrix of the object
		const glm::mat4 matrix();

		/// \brief Draw object
		void draw() const;
        

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

		/// \brief is the object static ? (ref)
		bool& isStatic() { return _isStatic; }

	// MEMBERS
	protected:
		/// \brief position of the object relative to the spline
		glm::vec3 _sPosition;
		/// \brief scale of the object
		glm::vec3 _scale;
		/// \brief rotation of the object folowing the 3 spline-reference vectors (fwd, left, up) in trigonometric rotation direction
		glm::vec3 _rotation;
		/// \brief model of the 3D object
		//std::unique_ptr<Model> _model; // better to use ptr because you can't reassign refs ?
		const Model& _model; // better to use refs because less mistakes ?

		/// \brief type of the gameObject : PLAYER, OBSTACLE, BONUS ...
		int _type;

		/// \brief is the object static ? 
		bool _isStatic = false;
		/// \brief stored transformation matrix of the object in case the object is static
		bool _hasMatrix = false;
		glm::mat4 _transformMat;

};

}

#endif