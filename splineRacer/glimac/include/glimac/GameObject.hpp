#ifndef __GAME__OBJECT
#define __GAME__OBJECT

#pragma once

class GameObject 
{
	public:
		GameObject();
		GameObject(const float angle, const float distance, const float progression);
		~GameObject();

		// Left - Right
		inline void angle(const float angle) {
			_sPosition.x = angle;
		}

		// Up - Down
		inline void distance(const float distance) {
			_sPosition.y = distance;
		}

		// Progress On the spline
		inline void progression(const float progression) {
			_sPosition.z = progression;
		}


	protected:
		glm::vec3 _sPosition; // x: Angle, y: Distance, z: Progression on the spline
};

#endif