#pragma once
#ifndef __GAMEOBJECT__HPP
#define __GAMEOBJECT__HPP

#include <GL/glew.h>
#include "common.hpp"

namespace splineengine {

/// \brief represents a object in the game, with a position and a set of colliders
class GameObject {
	// METHODS
	public:
		// CONSTRUCTORS - DESTRUCTORS
	    /// \brief default constructor (position(0.f,0.f,0.f), no colliders)
		GameObject()
			:_sPosition(0.f,0.f,0.f)
		{};

		/// \brief constructor from parameters
		/// \param position : glm::vec3 position of the object (relative to the spline)
		GameObject(const glm::vec3& sPosition)
			:_sPosition(sPosition)
		{};

		/// \brief copy constructor
		/// \param g : GameObject to copy from
		GameObject(const GameObject& g)
			:_sPosition(g._sPosition)
		{};

		/// \brief destructor
		~GameObject()
		{};


		//CONST GETTERS
		/// \brief get the position of the object (relative to the spline) as a const reference
		const glm::vec3& sPosition() const { return _sPosition; }

		// NON-CONST GETTERS (can be used as setters)
		/// \brief get the position of the object (relative to the spline) as a reference
		glm::vec3& sPosition() { return _sPosition; }
		
	// MEMBERS
	protected:
		// \brief position of the object relative to the spline
		glm::vec3 _sPosition;
		// TODO
		// \brief colliders of the object
		//std::vector<collider> _colliders;
};
}
#endif