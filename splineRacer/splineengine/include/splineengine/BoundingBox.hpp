#pragma once
#ifndef __COLLIDER__HPP
#define __COLLIDER__HPP

#include <vector>
#include <glimac/glm.hpp>

namespace splineengine {

class BoundingBox
{
	public:
		// CONSTRUCTORS - DESTRUCTORS
		/// \brief bounding box 
		BoundingBox(glm::vec3 min, glm::vec3 max);

		/// \brief destructor
		~BoundingBox();
    

		// METHODS
		bool collideWith(BoundingBox other, glm::vec3 selfPos, glm::vec3 otherPos);

	// MEMBERS
	private:
	    glm::vec3 _min;
	    glm::vec3 _max;
};

}
#endif