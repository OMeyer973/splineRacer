#ifndef __TRACKBALL__CAMERA__HPP
#define __TRACKBALL__CAMERA__HPP

#pragma once

#include <splineengine/Camera.hpp>

namespace splineengine {

// camera distance to the plane (size of the plane on screen)
const float camDistToPlayer = 10.f;
// camera distance to the plane (size of the plane on screen)
const float maxDistance = 0.f;
const float minDistance = -15.f;

class TrackballCamera : public Camera
{
	public:
		TrackballCamera();
		~TrackballCamera();
		
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

		/// \brief Update camera zoom
		void update();

	private:
		/// \brief Distance of the camera
		float _fDistance;
		/// \brief Distance of the camera
		float _zoom;
		/// \brief Horizontal angle
		float _fAngleX;
		/// \brief Vertical angle
		float _fAngleY;
};

}

#endif