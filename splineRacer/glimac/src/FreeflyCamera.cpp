#include <glimac/SDLWindowManager.hpp>
#include <glimac/FreeflyCamera.hpp>
#include <math.h>
#include <iostream>

// Constructor
FreeflyCamera::FreeflyCamera()
	:_Position(glm::vec3(0.0f, 0.0f, 0.0f)), 
	 _fPhi(M_PI),
	 _fTheta(0.0f)
{
	computeDirectionVectors();
}

// Destructor
FreeflyCamera::~FreeflyCamera() 
{}

// Methods
void FreeflyCamera::computeDirectionVectors() {
	_FrontVector = glm::vec3(cos(_fTheta)*sin(_fPhi), 
							  sin(_fTheta), 
							  cos(_fTheta)*cos(_fPhi));
	_LeftVector = glm::vec3(sin(_fPhi+M_PI/2),
							 0, 
							 cos(_fPhi+M_PI/2));
	_UpVector = glm::cross(_FrontVector, _LeftVector);
}

void FreeflyCamera::moveLeft(float t) {
	_Position += t * _LeftVector;
	computeDirectionVectors();
}

void FreeflyCamera::moveFront(float t) {
	_Position += t * _FrontVector;
	computeDirectionVectors();
}

void FreeflyCamera::rotateLeft(float degrees) {
	_fPhi += glm::radians(degrees);
	computeDirectionVectors();
}

void FreeflyCamera::rotateUp(float degrees) {
	_fTheta += glm::radians(degrees);
	computeDirectionVectors();
}

glm::mat4 FreeflyCamera::getViewMatrix() const {
	return glm::lookAt(_Position, _Position+_FrontVector, _UpVector);
}
