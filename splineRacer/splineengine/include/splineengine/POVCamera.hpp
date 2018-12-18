#ifndef __POV__CAMERA__HPP
#define __POV__CAMERA__HPP

#pragma once

#include <splineengine/Camera.hpp>

namespace splineengine {

const float POV_MAX_ANGLE_UP = glm::radians(15.f); // Limit vertical angle
const float POV_MAX_ANGLE_DOWN = glm::radians(20.f); // Limit horizontal angle

/// \brief Point of view Camera
class POVCamera : public Camera
{
	public:
		POVCamera();
		~POVCamera();

		/// \brief Zoom in and out (Trackball Camera only)
		/// \param delta : float value of the zoom
		void moveFront(float delta);

		/// \brief Rotate on the horizontal axis
		/// \param degrees : float value of the rotation
		void rotateLeft(float degrees);

		/// \brief Rotate on the vertical axis
		/// \param degrees : float value of the rotation
		void rotateUp(float degrees);

		/// \brief Get the camera view matrix
		glm::mat4 getViewMatrix() const;

	private:
		/// \brief Position of the camera
		glm::vec3 _position;
		/// \brief Horizontal angle
		float _fPhi;
		/// \brief Vertical angle
		float _fTheta;
		/// \brief Vector pointing to the front of the camera
		glm::vec3 _frontVector;
		/// \brief Vector pointing to the left of the camera
		glm::vec3 _leftVector;
		/// \brief Vector pointing to the top of the camera
		glm::vec3 _upVector;

		/// \brief Calculate _frontVector, _leftVector and _upVector based on the angles
		void computeDirectionVectors();
};

}

#endif