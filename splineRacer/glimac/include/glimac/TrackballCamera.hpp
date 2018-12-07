#ifndef __TRACKBALL__CAMERA
#define __TRACKBALL__CAMERA

#pragma once

class TrackballCamera 
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

#endif