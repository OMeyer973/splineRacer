#pragma once
#ifndef __LIGHT__HPP
#define __LIGHT__HPP

#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>

struct Light {
    glm::vec3 intensity;
    //glm::vec3 direction;
    // glm::vec3 inDirection
    Light(glm::vec3 inIntensity, ) {
        intensity = inIntensity;
        //direction = inDirection;
    }
};


#endif
