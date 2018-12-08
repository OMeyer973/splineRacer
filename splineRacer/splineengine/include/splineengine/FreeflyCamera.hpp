#ifndef __FREEFLY__CAMERA__HPP
#define __FREEFLY__CAMERA__HPP

#pragma once

namespace splineengine {

class FreeflyCamera
{
	public:
		FreeflyCamera();
		~FreeflyCamera();
		
		void moveLeft(float t);
		void moveFront(float t);
		void rotateLeft(float degrees);
		void rotateUp(float degrees);
		glm::mat4 getViewMatrix() const;

	private:
		glm::vec3 _Position;
		float _fPhi;
		float _fTheta;
		glm::vec3 _FrontVector;
		glm::vec3 _LeftVector;
		glm::vec3 _UpVector;

		void computeDirectionVectors();
};

}

#endif