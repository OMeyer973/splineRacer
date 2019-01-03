#include <glimac/SDLWindowManager.hpp>
#include <splineengine/TrackballCamera.hpp>
#include <iostream>

namespace splineengine {

// Constructor
TrackballCamera::TrackballCamera()
	:_fDistance(-camDistToPlayer), _fAngleX(0.0f), _fAngleY(0.0f), _zoom(-camDistToPlayer)
{}

// Destructor
TrackballCamera::~TrackballCamera()
{}

// Methods
void TrackballCamera::moveFront(const float delta) {
	_zoom += 2*delta;
	if (_zoom > maxDistance) {
		_zoom = maxDistance;
	} else if (_zoom < minDistance) {
		_zoom = minDistance;
	}
}

void TrackballCamera::rotateLeft(const float degrees) {
	_fAngleY += degrees;
}

void TrackballCamera::rotateUp(const float degrees) {
	_fAngleX += degrees;
}

glm::mat4 TrackballCamera::getViewMatrix() const {
	glm::mat4 ViewMatrix = glm::mat4();
	ViewMatrix = glm::translate(ViewMatrix, glm::vec3(0, 0, _fDistance));
	ViewMatrix = glm::rotate(ViewMatrix, glm::radians(_fAngleX), glm::vec3(1, 0, 0));
	ViewMatrix = glm::rotate(ViewMatrix, glm::radians(_fAngleY), glm::vec3(0, 1, 0));
	return ViewMatrix;
}

void TrackballCamera::update() {
	_fDistance = glm::mix(_fDistance, _zoom, 1/8.f);
}

} // namespace splineengine
