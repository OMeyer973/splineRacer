#include <glimac/SDLWindowManager.hpp>
#include <splineengine/Camera.hpp>
// #include <math.h>
// #include <iostream>

namespace splineengine {

// Constructor
Camera::Camera()
	:_position(glm::vec3(0.0f, 0.0f, 0.0f))
{}

// Destructor
Camera::~Camera() 
{}

} // namespace splineengine
