#ifndef __POV__CAMERA__HPP
#define __POV__CAMERA__HPP

#pragma once

#include <splineengine/Camera.hpp>

namespace splineengine {

const float POV_MAX_ANGLE_UP = glm::radians(15.f);
const float POV_MAX_ANGLE_DOWN = glm::radians(20.f);

/// \brief Point of view Camera
class POVCamera : public Camera
{
	public:
		POVCamera();
		~POVCamera();

		void moveFront(float delta);
		void rotateLeft(float degrees);
		void rotateUp(float degrees);
		glm::mat4 getViewMatrix() const;

	private:
		glm::vec3 _position;
		float _fPhi;
		float _fTheta;
		glm::vec3 _frontVector;
		glm::vec3 _leftVector;
		glm::vec3 _upVector;

		void computeDirectionVectors();
};

}

#endif