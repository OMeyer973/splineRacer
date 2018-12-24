#include <splineengine/Collider.hpp>
#include <iostream>

namespace splineengine {

// Constructors
Collider::Collider()
{}

// Destructor
Collider::~Collider()
{}

bool Collider::collideWith(Collider other, glm::mat4 selfTransformMat, glm::mat4 otherTransformMat) {

	// multiplication of homogenous coordinates with 4 components and immediate cast to vec3
	glm::vec3 selfWorldPos(glm::vec4(_position,1.f) * selfTransformMat);

	glm::vec3 otherWorldPos(glm::vec4(other._position,1.f) * otherTransformMat);

	if (glm::distance(selfWorldPos, otherWorldPos) < _radius*_radius + other._radius*other._radius) {
		std::cout << "COLLISION" << std::endl;
	}

	return false;
}


}