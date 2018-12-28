#pragma once
#ifndef __COLLECTABLE__HPP
#define __COLLECTABLE__HPP

#include "GameObject.hpp"
#include "common.hpp"

const float collectableRotationSpeed = .015f;

namespace splineengine {

/// \brief Represents a collectable Gameobject
class Collectable : public GameObject {
    // METHODS
    public:

    	Collectable(const GameObject& gameObject = GameObject(Model(), Spline(), false));

        /// \brief trigger collision behavior when colliding with another Gameobjects. 
        void doCollisionWith(GameObject other) {
            if (debug) std::cout << "collectable doing collision " << std::endl;
        };

        void update(const float dt, const float pos) {
			_rotation.z += dt + (pos*collectableRotationSpeed) * dt;
		}

};

}

#endif
