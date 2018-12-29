#pragma once
#ifndef __COLLECTABLE__HPP
#define __COLLECTABLE__HPP

#include "GameObject.hpp"
#include "common.hpp"

const float collectableRotationSpeed = 0.2f;

namespace splineengine {

class Player;

/// \brief Represents a Collectable Gameobject
class Collectable : public GameObject {
    // METHODS
    public:

    	Collectable(const GameObject& gameObject = GameObject(Model(), Spline(), false));

        /// \brief Collectable Destructor
    	virtual ~Collectable() {
    		// if (debug) std::cout << "Collectable Destructor called" << std::endl;
    	};

        /// \brief trigger collision behavior when colliding with another Gameobjects. 
        void doCollisionWith(GameObject& other) {
            if (debug) std::cout << "Collectable doing collision with GameObject" << std::endl;
        };

        /// \brief trigger collision behavior when colliding with another Gameobjects. 
        void doCollisionWith(Player& other) {
            if (debug) std::cout << "Collectable doing collision with Player" << std::endl;
        };

        void update(const float dt, const float pos) {
			_rotation.z += dt + (pos*collectableRotationSpeed) * dt;
		}

};

}

#endif
