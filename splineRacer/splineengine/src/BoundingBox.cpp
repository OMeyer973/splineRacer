#include <splineengine/BoundingBox.hpp>


namespace splineengine {

// Constructors
BoundingBox::BoundingBox(glm::vec3 min, glm::vec3 max)
	:_min(min), _max(max)
{
	// TODO : swap min & max if necessary, or throw error, idk
}

// Destructor
BoundingBox::~BoundingBox()
{}

bool collideWith(BoundingBox other, glm::vec3 selfPos, glm::vec3 otherPos) {
	// TODO : if, if, if, if ...

	return false;
}


}