#pragma once
#ifndef __PLAYER__HPP
#define __PLAYER__HPP

#include "common.hpp"

namespace glimac {

// Represents the player
class Player {

public:
    /// \brief player Constructor
    Player()
    {};
    /// \brief player Destructor
    ~Player()
    {};
    



protected:
    // (float) speed of the player - x : left speed - y : up speed -z : forward speed;  
    glm::vec3 _speed;
    
    // (float) maximum speed of the player - x : left speed - y : up speed -z : forward speed;  
    glm::vec3 _maxSpeed;

    float _fwdSpeed = 1.f;
    
    float _angle = 0.f;
    float _maxRotSpeed = 0.01f;
    float _rotSpeed = 0.f; // >0 pour droite, <0 pour gauche
};
    
}

#endif