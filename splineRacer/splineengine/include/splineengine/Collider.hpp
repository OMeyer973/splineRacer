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
		// const std::vector<BoundingBox>& boxes() const { return _boxes; };
		

        // SETTER
		// void pushBox (BoundingBox box) { _boxes.push_back(box); };
		
		// METHODS
		// brief is the Collider colliding with another collider ? 
		// brief please provide self position and other position
		bool collideWith(Collider other, glm::vec3 selfPos, glm::vec3 otherPos);

	// MEMBERS
	protected:
		//std::vector<BoundingBox> _boxes;		
		//TODO : add single big bounding box to collider
};

}
#endif