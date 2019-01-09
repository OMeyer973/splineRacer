#pragma once
#ifndef __OBSTACLE__HPP
#define __OBSTACLE__HPP

#include "common.hpp"
#include "GameObject.hpp"
#include "Player.hpp"

namespace splineengine {

class Player;

/// \brief Represents an obstacle Gameobject
class Obstacle : public GameObject {
    // METHODS
    public:
    	/// \brief Obstacle Constructor
    	Obstacle(const GameObject& gameObject = GameObject(Model(), Spline(),"default.png", false));

    	/// \brief Obstacle Destructor
    	~Obstacle()
    	{};

        /// \brief trigger collision behavior when colliding with another Gameobjects.
        void doCollisionWith(GameObject& other) {
            if (debug) std::cout << "obstacle collision with GameObject" << std::endl;
        };

        /// \brief trigger collision behavior when colliding with another Gameobjects.
        void doCollisionWith(Player& other) {
            if (debug) std::cout << "obstacle collision with Player" << std::endl;
        };

};

}

#endif
