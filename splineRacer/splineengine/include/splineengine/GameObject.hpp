#pragma once
#ifndef __GAMEOBJECT__HPP
#define __GAMEOBJECT__HPP

#include <GL/glew.h>
#include <iostream>
#include "common.hpp"

namespace splineengine {

/// \brief represents a object in the game, with a position and a set of colliders
class GameObject {
	// METHODS
	public:
		// CONSTRUCTORS - DESTRUCTORS
	    /// \brief default constructor (position(0.f,0.f,0.f), no colliders)
		GameObject()
			:_sPosition(0.f,0.f,0.f), _Rotation(0.f,0.f,0.f), _Scale(1.f,1.f,1.f)
		{};

		/// \brief constructor from parameters
		/// \param position : glm::vec3 position of the object (relative to the spline)
		GameObject(const glm::vec3& sPosition)
			:_sPosition(sPosition)
		{};


		/// \brief constructor from parameters
		/// \param position : glm::vec3 position of the object (relative to the spline)
		GameObject(glm::vec3 sPosition,  glm::vec3 rotation,  glm::vec3 scale)
			:_sPosition(sPosition), _Rotation(rotation), _Scale(scale)
		{
			std::cout << "_sPosition " << _sPosition << std::endl;
			std::cout << "_Rotation " << _Rotation << std::endl;
			std::cout << "_Scale " << _Scale << std::endl;
			
		};


		/// \brief copy constructor
		/// \param g : GameObject to copy from
		GameObject(const GameObject& g)
			:_sPosition(g._sPosition)
		{};

		/// \brief destructor
		~GameObject()
		{};

		void print() {
			std::cout << std::endl;
			std::cout << "print" << std::endl;
			std::cout << "_sPosition " << _sPosition << std::endl;
			std::cout << "_Rotation " << _Rotation << std::endl;
			std::cout << "_Scale " << _Scale << std::endl;
			std::cout << "/print" << std::endl;
			std::cout << std::endl;
		}

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
		glm::vec3 _Rotation;
		glm::vec3 _Scale;
		// TODO
		// \brief colliders of the object
		//std::vector<collider> _colliders;
};
}
#endif