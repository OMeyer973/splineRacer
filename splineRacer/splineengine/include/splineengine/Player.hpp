#pragma once
#ifndef __PLAYER__HPP
#define __PLAYER__HPP

#include "GameObject.hpp"

namespace splineengine {

// Represents the player
class Player : public GameObject 
{

public:
    /// \brief player Constructor
    Player() {
        _sPosition = glm::vec3(0.f, 0.6f, 0.f);
        _speed = glm::vec3(0.f, 0.f, 1.f);
        _maxSpeed = glm::vec3(0.01f, 0.005f, 0.01f);
    };
    /// \brief player Destructor
    ~Player()
    {};
    
    /// \brief update player position 
    void speed() {

    };


    /// \brief update player position 
    void updatePosition() {

    };
    


protected:
    // (float) speed of the player - x : left speed - y : up speed -z : forward speed;  
    glm::vec3 _speed;

    // (float) maximum speed of the player - x : left speed - y : up speed -z : forward speed;  
    glm::vec3 _maxSpeed;
};
    
}

#endif