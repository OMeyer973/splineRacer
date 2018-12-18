#include <glimac/SDLWindowManager.hpp>
#include <splineengine/POVCamera.hpp>
#include <math.h>
#include <iostream>

namespace splineengine {

// Constructor
POVCamera::POVCamera()
	:_position(glm::vec3(0.0f, 0.0f, 5.0f)), 
	 _fPhi(M_PI),
	 _fTheta(0.0f)
{
	computeDirectionVectors();
}

// Destructor
POVCamera::~POVCamera() 
{}

// Methods
void POVCamera::moveFront(const float delta) {
	return;
}

void POVCamera::computeDirectionVectors() {
	_frontVector = glm::vec3(cos(_fTheta)*sin(_fPhi), 
							  sin(_fTheta), 
							  cos(_fTheta)*cos(_fPhi));
	_leftVector = glm::vec3(sin(_fPhi+M_PI/2),
							 0, 
							 cos(_fPhi+M_PI/2));
	_upVector = glm::cross(_frontVector, _leftVector);
}

void POVCamera::rotateLeft(float degrees) {
	_fPhi += glm::radians(degrees);
	if (fabs(_fPhi) > M_PI + POV_MAX_ANGLE_DOWN)
		_fPhi = M_PI + POV_MAX_ANGLE_DOWN;
	if (fabs(_fPhi) < M_PI - POV_MAX_ANGLE_DOWN)
		_fPhi = M_PI - POV_MAX_ANGLE_DOWN;
	computeDirectionVectors();
}

void POVCamera::rotateUp(float degrees) {
	_fTheta += glm::radians(degrees);
	if (fabs(_fTheta) > POV_MAX_ANGLE_UP)
		_fTheta = POV_MAX_ANGLE_UP * _fTheta / fabs(_fTheta);
	computeDirectionVectors();
}

glm::mat4 POVCamera::getViewMatrix() const {
	return glm::lookAt(_position, _position+_frontVector, _upVector);
}

} // namespace splineengine
