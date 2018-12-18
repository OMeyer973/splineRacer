#pragma once
#ifndef __GAMEOBJECT__HPP
#define __GAMEOBJECT__HPP

#include "common.hpp"
#include "Spline.hpp"

namespace splineengine {

/// \brief represents a object in the game, with a position and a set of colliders
class GameObject {
	// METHODS
	public:
		// CONSTRUCTORS - DESTRUCTORS
	    /// \brief default constructor (position(0.f,0.f,0.f), no colliders)
		GameObject()
			:_sPosition(0.f,0.f,0.f), _scale(1.f,1.f,1.f), _rotation(0.f,0.f,0.f)
		{};

		/// \brief constructor from parameters
		/// \param position : glm::vec3 position of the object (relative to the spline)
		GameObject(const glm::vec3& sPosition)
			:_sPosition(sPosition), _scale(1.f,1.f,1.f), _rotation(0.f,0.f,0.f)
		{};

		/// \brief constructor from parameters
		/// \param position : glm::vec3 position of the object (relative to the spline)
		/// \param position : glm::vec3 scale    of the object 
		/// \param position : glm::vec3 rotation of the object 
		GameObject(const glm::vec3& sPosition, const glm::vec3& scale, const glm::vec3& rotation)
			:_sPosition(sPosition), _scale(scale), _rotation(rotation)
		{};


		/// \brief copy constructor
		/// \param g : GameObject to copy from
		GameObject(const GameObject& g)
			:_sPosition(g._sPosition), _scale(g._scale), _rotation(g._rotation)
		{};

		/// \brief destructor
		~GameObject()
		{};


        // METHODS
		/// \brief returns the transform matrix of the object in the given spline reference
		glm::mat4 const matrix(Spline& spline);
        

		//CONST GETTERS
		/// \brief get the position of the object (relative to the spline) as a const reference
		const glm::vec3& sPosition() const { return _sPosition; }

		/// \brief get the rotation of the object
		const glm::vec3& rotation() const { return _rotation; }

		/// \brief get the scale of the object
		const glm::vec3& scale() const { return _scale; }

		// NON-CONST GETTERS (can be used as setters)
		/// \brief get the position of the object (relative to the spline) as a reference
		glm::vec3& sPosition() { return _sPosition; }

		/// \brief get the rotation of the object
		glm::vec3& rotation() { return _rotation; }

		/// \brief get the scale of the object
		glm::vec3& scale() { return _scale; }
		
	// MEMBERS
	protected:
		// \brief position of the object relative to the spline
		glm::vec3 _sPosition;
		glm::vec3 _scale;
		glm::vec3 _rotation;
};
}
#endif