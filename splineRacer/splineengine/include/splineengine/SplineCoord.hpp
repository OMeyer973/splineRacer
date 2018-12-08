#pragma once
#ifndef __SPLINECOORD__HPP
#define __SPLINECOORD__HPP

#include <iostream>

namespace splineengine {

/// \brief represents a point in the spline reference : forward, left (angle), up
class SplineCoord {
	// METHODS
	public:
		// CONSTRUCTORS - DESTRUCTORS
	    /// \brief default constructor (fwd = left = up = 0.f)
		SplineCoord()
			:_sPosition(0.f, 0.f, 0.f)
		{};
		
	    /// \brief constructor from parameters
		/// \param fwd  : forward distance folowing the spline
		/// \param left : angle to the normal vector of the spline (trigonometric direction, ie rotating left is positive)
		/// \param up   : normal distance to the spline
		SplineCoord(const float fwd, const float left, const float up)
			:_sPosition(fwd, left, up)
		{
			//std::cout << _sPosition.x << std::endl;
		};

		///\brief copy constructor
		/// \param s : SplineCoord to copy from
		SplineCoord(const SplineCoord& s)
		:_sPosition(s._sPosition)
		{};

	    /// \brief destructor
		~SplineCoord()
		{};
		
		//CONST GETTERS
		/// \brief get the fwd coord (forward distance folowing the spline) as a const reference 
		const float& fwd() const {
			return _sPosition.x;
		}
	    /// \brief get the left coord (angle to the normal vector of the spline) as a const reference
		const float& left() const {
			return _sPosition.y;
		}
	    /// \brief get the up coord as a const reference (normal distance to the spline)
		const float& up() const {
			return _sPosition.z;
		}

		// NON-CONST GETTERS (can be used as setters)
		/// \brief get the fwd coord as a reference (forward distance folowing the spline) 
		float& fwd() {
			return _sPosition.x;
		}
		// TODO : when setting the left value, set it modulo 2*PI
		// ^ how to do this when you have a non-const getter as a setter and no real setter ?
	    /// \brief get the left coord as a reference (angle to the normal vector of the spline)
		float& left() {
			return _sPosition.y;
		}
	    /// \brief get the up coord as a reference (normal distance to the spline)
		float& up() {
			return _sPosition.z;
		}

		// TODO 
		// OPERATORS

	// MEMBERS
	protected:
		/// \brief sPosition stands for for spline position
		/// \param x: fwd, y: left, z: p
		glm::vec3 _sPosition;
};
}
#endif