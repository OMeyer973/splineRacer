#include <splineengine/Collider.hpp>


namespace splineengine {

// Constructors
Collider::Collider()
{}

// Destructor
Collider::~Collider()
{}

bool collideWith(Collider other, glm::vec3 selfPos, glm::vec3 otherPos) {
	// for (size_t i = 0; i<_boxes.length(); ++i) {
	// 	for (size_t j = 0; j<other._boxes.length(); ++j) {
	// 		// todo : add distance factor for cylindrical coordinates projection
	// 		if (_boxes[i].collideWith(other._boxes[j], selfPos, otherPos))
	// 			return true;
	// 	}
	// }
	return false;
}


}