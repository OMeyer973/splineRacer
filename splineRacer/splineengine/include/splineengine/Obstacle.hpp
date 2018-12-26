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
        void update(const float dt);

        /// \brief trigger collision behavior when colliding with another Gameobjects. 
        void doCollisionWith(GameObject other) {
            std::cout << "obstacle doing collision " << std::endl;
        };

};

}
#endif
