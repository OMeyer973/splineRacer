#pragma once
#ifndef __PLAYER__HPP
#define __PLAYER__HPP

#include "GameObject.hpp"

namespace splineengine {

/// \brief Represents the player as a Gameobject but with more useful stuff
class Player : public GameObject {
    // METHODS
    public:
        // CONSTRUCTORS - DESTRUCTORS
        /// \brief default player Constructor
        Player() 
            :GameObject(SplineCoord(0.f,0.f,0.6f)),
            _speed(0.005f, 0.f, 0.f),
            _maxSpeed(1.f, 0.1f, 0.05f)
        {};

        /// \brief player Destructor
        ~Player()
        {};
        
        // CONST GETTERS
        /// \brief get the speed of the player (relative to the spline) as a const reference
        const SplineCoord& speed() const {
            return _speed;
        }

        /// \brief get the speed of the player (relative to the spline) as a const reference
        const SplineCoord& maxSpeed() const {
            return _maxSpeed;
        }

        // NON-CONST GETTERS (can be used as setters)
        /// \brief get the speed of the player (relative to the spline) as a reference
        SplineCoord& speed() {
            return _speed;
        }

        /// \brief get the maximum speed of the player (relative to the spline) as a reference
        SplineCoord& maxSpeed() {
            return _maxSpeed;
        }

        /// \brief update the player position using it's current speed
        void updatePosition();

    // MEMBERS        
    protected:
        // \brief position of the object relative to the spline
        SplineCoord _speed;
        SplineCoord _maxSpeed;
};        
}
#endif