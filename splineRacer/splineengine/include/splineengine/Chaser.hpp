#pragma once
#ifndef __CHASER__HPP
#define __CHASER__HPP

#include <memory>
#include "common.hpp"
#include "GameObject.hpp"
#include "Player.hpp"

namespace splineengine {

const float defaultChaserDelay = 3.0f;
const float ChaserLagFactor = 0.002f; // how fast the chaser is going back to his initial delayed position
const float chaserLateralSpeed = 0.1f; // 0-1 how fast is the chaser to catch up with the player (left-right)
const float chaserRotateSpeed = 6.f;
const float chaserWiggleAmp = 0.5f;
const float chaserWiggleFreq = 2.5f;

class Player;

/// \brief Represents an obstacle Gameobject
class Chaser : public GameObject {
    // METHODS
    public:
    	/// \brief Chaser Constructor
    	Chaser(const GameObject& gameObject, const Player& player, float delay = defaultChaserDelay);

        /// \brief Chaser Destructor
        ~Chaser()
        {};

        // CONST GETTER
        /// \brief is the chaser chasing the player ?
         const bool& chasingPlayer() const { return _chasingPlayer; }

        // NON CONST GETTER
    	/// \brief is the chaser chasing the player ?
         bool& chasingPlayer() { return _chasingPlayer; }

        
        /// \brief update the chaser status at each frame
        void update();

        /// \brief trigger collision behavior when colliding with the player. 
        void doCollisionWith(Player& other);

    //MEMBERS
    private:
    	const Player& _player;
        bool _chasingPlayer = true;
        bool _chatchedPlayer = false;
        // how far behind the player the chaser is ? (max value)
        float _delay;
};

}

#endif
