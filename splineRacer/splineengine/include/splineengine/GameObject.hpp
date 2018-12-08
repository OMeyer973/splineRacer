#pragma once
#ifndef __GAMEOBJECT__HPP
#define __GAMEOBJECT__HPP

#include "SplineCoord.hpp"

namespace splineengine {

/// \brief represents a object in the game, with a position and a set of colliders
class GameObject {
	// METHODS
	public:
		// CONSTRUCTORS - DESTRUCTORS
	    /// \brief default constructor (position(0.f,0.f,0.f), no colliders)
		GameObject()
			:_position(0.f,0.f,0.f)
		{};

		/// \brief constructor from parameters
		/// \param position : SplineCoord position of the object (relative to the spline)
		GameObject(const SplineCoord& position)
			:_position(position)
		{};

		/// \brief copy constructor
		/// \param g : GameObject to copy from
		GameObject(const GameObject& g)
			:_position(g._position)
		{};

		/// \brief destructor
		~GameObject()
		{};

		//CONST GETTERS
		/// \brief get the position of the object (relative to the spline) as a const reference
		const SplineCoord& position() const {
			return _position;
		}

		// NON-CONST GETTERS (can be used as setters)
		/// \brief get the position of the object (relative to the spline) as a reference
		SplineCoord& position() {
			return _position;
		}
		
	// MEMBERS
	protected:
		// \brief position of the object relative to the spline
		SplineCoord _position;
		// TODO
		// \brief colliders of the object
		//std::vector<collider> _colliders;
};
}
#endif