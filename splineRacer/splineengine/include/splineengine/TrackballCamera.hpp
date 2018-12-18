#ifndef __TRACKBALL__CAMERA__HPP
#define __TRACKBALL__CAMERA__HPP

#pragma once

#include <splineengine/Camera.hpp>

namespace splineengine {

class TrackballCamera : public Camera
{
	public:
		TrackballCamera();
		~TrackballCamera();
		
		void moveFront(float delta);
		void rotateLeft(float degrees);
		void rotateUp(float degrees);

		glm::mat4 getViewMatrix() const;

	private:
		float _fDistance;
		float _fAngleX;
		float _fAngleY;
};

}

#endif