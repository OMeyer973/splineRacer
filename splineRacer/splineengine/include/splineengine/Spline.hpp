#pragma once
#ifndef __SPLINE__HPP
#define __SPLINE__HPP

#include <GL/glew.h>
#include <glimac/SDLWindowManager.hpp>
#include <glm/gtc/noise.hpp>
#include "Common.hpp"

namespace splineengine {

// delta position used to rotate the camera and the objects facing the curve
// it is large in order to have smooth camera movements
const float dx = 1.f;
// the higher the camera is, the lower it looks on the spline following this factor
const float lookDownFactor = 0.1f;


/// \brief Represents the spline, its equation and transforms
class Spline {
    // METHODS
    public:
        // CONSTRUCTORS - DESTRUCTORS
        /// \brief default spline Constructor
        Spline() 
        {};

        /// \brief spline Destructor
        ~Spline()
        {};

        // CONST GETTERS
        // none for now
        
        // NON-CONST GETTERS (can be used as setters)
        // none for now

        // METHODS
        /// \brief evaluate the spline at the forward coordinate t and returns the world-space vec3 point corresponding
        glm::vec3 point(const float t);

        /// \brief returns the transforma matrix for the camera at the given point
        glm::mat4 camMatrix(const glm::vec3 sPoint);
        
        /// \brief returns the transforma matrix for an object the given point
        glm::mat4 matrix(const glm::vec3 sPoint);




    // MEMBERS        
    //protected:
        // TODO : make spline from list of vec3
        //  std::vector<glm::vec3> anchors;
};        
}
#endif