#pragma once
#ifndef __COLLIDER__HPP
#define __COLLIDER__HPP

#include <glimac/glm.hpp>
#include "common.hpp"

namespace splineengine {

const float defaultColliderRadius = 1.f;

class Collider {
	public:
	// METHODS
		// CONSTRUCTORS - DESTRUCTORS
		/// \brief default colider : center (0,0,0), radius 1
		Collider(
			const glm::vec3& position = glm::vec3(0),
			const float radius = defaultColliderRadius
		);

		/// \brief destructor
		~Collider();

        // CONST GETTERS
		

        // SETTER
		
		// METHODS
		// brief is the Collider intersecting another collider ? 
		// brief please provide self transform matrix, self scale, other transform matrix & other scale
		bool intersect(const Collider other, 
			const glm::mat4 selfTransformMat, const float selfScale, 
			const glm::mat4 otherTransformMat, const float otherScale) const;
	// MEMBERS
	protected:
		glm::vec3 _position;
		float _radius;
};

}
#endif