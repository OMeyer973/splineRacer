#pragma once
#ifndef __SPLINE__HPP
#define __SPLINE__HPP

#include <iostream>

#include <vector>
#include <cmath>
#include <GL/glew.h>
#include<glm/gtc/random.hpp>
#include <glm/gtc/noise.hpp>
#include <glimac/SDLWindowManager.hpp>
#include "common.hpp"


namespace splineengine {

// delta position used to rotate the camera and the objects facing the curve
// it is large in order to have smooth camera movements
const float dt = 0.1f;
// the higher the camera is, the lower it looks on the spline following this factor
const float lookDownFactor = 0.1f;


/// \brief Represents the spline, its equation and transforms
class Spline {
    // METHODS
    public:
        // CONSTRUCTORS - DESTRUCTORS
        /// \brief default random spline constructor spline with 10 anchors
        Spline();

        /// \brief random spline constructor with given number of anchors
        Spline(const int nbAnchors);

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




    protected:
        /// \brief wrap i between 0-loopSize.
        /// \brief behaves like % for i>0 
        int loopInt (int i, int loopSize);

        /// \brief Returns a position between 4 Vector3 with Catmull-Rom spline algorithm
        /// \brief (when t goes between 0-1, position goes between p1-p2. p0, p3 are just control points)
        glm::vec3 GetCatmullRomPosition(float t, glm::vec3 p0, glm::vec3 p1, glm::vec3 p2, glm::vec3 p3);
        // MEMBERS        
        
        // TODO : make spline from list of vec3
         std::vector<glm::vec3> _anchors;
};        
}
#endif