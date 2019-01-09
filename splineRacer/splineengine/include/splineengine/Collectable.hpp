#pragma once
#ifndef __COLLECTABLE__HPP
#define __COLLECTABLE__HPP

#include "GameObject.hpp"
#include "common.hpp"

const float collectableRotationSpeed = 2.f;

namespace splineengine {

class Player;

/// \brief Represents a Collectable Gameobject
class Collectable : public GameObject {
    // METHODS
    public:

    	Collectable(const GameObject& gameObject = GameObject(Model(), Spline(),"default.png",false));

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
            _isTaken = true;
        };

        /// \brief Animate collectable
        void update(const glm::vec3 playerPos);

        /// brief
        const bool isTaken() const {
            return _isTaken;
        }

        const bool isHidden() const {
			return _isHidden;
		}

    private:
        bool _isTaken;
        bool _isHidden;

};

}

#endif
