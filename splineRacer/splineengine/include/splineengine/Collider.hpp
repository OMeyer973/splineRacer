#pragma once
#ifndef __BOUNDINGBOX__HPP
#define __BOUNDINGBOX__HPP

#include <vector>
#include <glimac/glm.hpp>
#include <splineengine/BoundingBox.hpp>

namespace splineengine {

class Collider
{
	public:
	// METHODS
		// CONSTRUCTORS - DESTRUCTORS
		/// \brief default colider : no bounding box
		Collider();

		/// \brief destructor
		~Collider();

        // CONST GETTERS
		

        // SETTER
		
		// METHODS
		// brief is the Collider colliding with another collider ? 
		// brief please provide self transform matrix & other transform matrix
		bool collideWith(Collider other, glm::mat4 selfTransformMat, glm::mat4 otherTransformMat);

	// MEMBERS
	protected:
		glm::vec3 _position;
		float _radius;
		//std::vector<BoundingBox> _boxes;		
		//TODO : add single big bounding box to collider
};

}
#endif