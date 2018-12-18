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
            :GameObject(glm::vec3(1.f,0.f,2.f)),
            _sSpeed(1.f, 0.f, 0.f),
            _sMaxSpeed(4.f, 10.f, 10.f),
            _sAcceleration(0.f, 20.f, 20.f)
        {};

        /// \brief player Destructor
        ~Player()
        {};

        
        // CONST GETTERS
        /// \brief get the speed of the player (relative to the spline) as a const reference
        //const glm::vec3& speed() const { return _sSpeed; }

        /// \brief get the speed of the player (relative to the spline) as a const reference
        //const glm::vec3& maxSpeed() const { return _sMaxSpeed; }

        /// \brief get the left-right input direction as a const 
        const float& goingLeft() const { return _sInput[LEFT]; }

        /// \brief get the up_down input direction as a const 
        const float& goingUp() const { return _sInput[UP]; }


        // NON-CONST GETTERS (can be used as setters)
        /// \brief get the speed of the player (relative to the spline) as a reference
        //glm::vec3& speed() { return _sSpeed; }

        /// \brief get the maximum speed of the player (relative to the spline) as a reference
        //glm::vec3& maxSpeed() { return _sMaxSpeed; }

        /// \brief get the left-right input direction as a reference
        float& goingLeft() { return _sInput[LEFT]; }

        /// \brief get the up_down input direction as a reference
        float& goingUp() { return _sInput[UP]; }


        // METHODS

        /// \brief update the player status at each frame
        void update(const float dt);


    protected:
        // METHODS
        /// \brief update the player speed using it's acceleration and inputs (goingLeft & goingUp)
        void updateSpeed(const float dt);

        /// \brief update the player position using it's current speed
        void updatePosition(const float dt);

        // MEMBERS        
        // \brief position of the object relative to the spline
        glm::vec3 _sSpeed;
        glm::vec3 _sMaxSpeed;
        /// \brief acceleration and decceleration of the player
        glm::vec3 _sAcceleration;
        
        /// \brief current input | [0] forward : no input | [1] left -> +1, straight -> 0, right -> -1 | [2] up -> +1, straight -> 0, down -> -1 
        glm::vec3 _sInput;

};        
}
#endif