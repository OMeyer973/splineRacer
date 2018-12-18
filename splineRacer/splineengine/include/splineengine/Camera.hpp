#ifndef __CAMERA__HPP
#define __CAMERA__HPP

#pragma once

namespace splineengine {

const unsigned int POV_CAMERA = 0;
const unsigned int TRACKBALL_CAMERA = 1;

/// \brief Camera is an abstract class, parent of TrackballCamera and POVCamera
class Camera
{
	public:
		Camera();
		~Camera();

		virtual void moveFront(float delta) = 0;
		virtual void rotateLeft(float degrees) = 0;
		virtual void rotateUp(float degrees) = 0;
		virtual glm::mat4 getViewMatrix() const = 0;

	private:
		glm::vec3 _position;
};

}

#endif