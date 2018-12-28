#pragma once
#ifndef __OBSTACLE__HPP
#define __OBSTACLE__HPP

#include "GameObject.hpp"
#include "common.hpp"

namespace splineengine {

/// \brief Represents an obstacle Gameobject
class Obstacle : public GameObject {
    // METHODS
    public:

    	Obstacle(const GameObject& gameObject = GameObject(Model(), Spline(), false));

        /// \brief trigger collision behavior when colliding with another Gameobjects. 
        void doCollisionWith(GameObject other) {
            if (debug) std::cout << "obstacle doing collision " << std::endl;
        };

};

}

#endif
