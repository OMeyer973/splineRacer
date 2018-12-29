#pragma once
#ifndef __PLAYER__HPP
#define __PLAYER__HPP

#include "common.hpp"
#include "GameObject.hpp"
#include "Obstacle.hpp"
#include "Settings.hpp"

namespace splineengine {

const glm::vec3 defaultPlayerPos          = glm::vec3(1.f, 0.f, 10.f);
const float     defaultPlayerFwdSpeed     = 1.5f;
const glm::vec3 defaultPlayerMaxSpeed     = glm::vec3(1.5f, 10.f, 10.f);
const glm::vec3 defaultPlayerAcceleration = glm::vec3(3.f, 7.f, 7.f);
const glm::vec3 defaultPlayerBounceFactor = glm::vec3(2.f, 4.f, 4.f); //careful with these or you can go through walls or get launched to infinity. above 2 looks kinda safe

const float collisionCooldowd = 2.f *  Settings::instance().deltaTime();
const float minPlayerUp = 1.f;
const float maxPlayerUp = 20.f;


/// \brief Represents the player as a Gameobject but with more useful stuff
class Player : public GameObject {
    // METHODS
    public:
        // CONSTRUCTORS - DESTRUCTORS
        /// \brief default player Constructor
        Player(
            const GameObject& gameObject  = GameObject(Model(), Spline(), false, defaultPlayerPos),
            const float       fwdSpeed     = defaultPlayerFwdSpeed,
            const glm::vec3   maxSpeed     = defaultPlayerMaxSpeed,
            const glm::vec3   acceleration = defaultPlayerAcceleration
        );

        /// \brief player Destructor
        ~Player()
        {};

        // Player& operator=(const Player& player) {
        // };
        

        // CONST GETTERS
        /// \brief get the speed of the player (relative to the spline) as a const reference
        const glm::vec3& speed() const { return _sSpeed; }

        /// \brief get the speed of the player (relative to the spline) as a const reference
        const glm::vec3& maxSpeed() const { return _sMaxSpeed; }

        /// \brief get the left-right input direction as a const
        const float& goingLeft() const { return _sInput[LEFT]; }

        /// \brief get the up_down input direction as a const
        const float& goingUp() const { return _sInput[UP]; }


        // NON-CONST GETTERS (can be used as setters)
        /// \brief get the speed of the player (relative to the spline) as a reference
        glm::vec3& speed() { return _sSpeed; }

        /// \brief get the maximum speed of the player (relative to the spline) as a reference
        glm::vec3& maxSpeed() { return _sMaxSpeed; }

        /// \brief get the left-right input direction as a reference
        float& goingLeft() { return _sInput[LEFT]; }

        /// \brief get the up_down input direction as a reference
        float& goingUp() { return _sInput[UP]; }


        // METHODS

        /// \brief update the player status at each frame
        void update(const float dt);

        /// \brief trigger collision behavior when colliding with another Gameobjects. 
        void doCollisionWith(GameObject other);

        /// \brief trigger collision behavior when colliding with another Gameobjects. 
        void doCollisionWith(Obstacle other);

        /// \brief Overriden function to draw the plane
        // void draw() const;

    protected:
        // METHODS
        /// \brief update the player speed using it's acceleration and inputs (goingLeft & goingUp)
        void updateSpeed(const float dt);

        /// \brief update the player position using it's current speed
        void updatePosition(const float dt);

        // MEMBERS
        // VARIABLES
        // \brief position of the object relative to the spline
        glm::vec3 _sSpeed;
        glm::vec3 _sMaxSpeed;
        /// \brief acceleration and decceleration of the player
        glm::vec3 _sAcceleration;

        /// \brief current input | [0] forward : no input | [1] left -> +1, straight -> 0, right -> -1 | [2] up -> +1, straight -> 0, down -> -1
        glm::vec3 _sInput;

        float _collisionCooldownTimer = 0;
        // CONSTANTS
};
}
#endif
