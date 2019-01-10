#pragma once
#ifndef __SPLINE__HPP
#define __SPLINE__HPP

#include <vector>
#include <cmath>
#include <string>
#include <glimac/SDLWindowManager.hpp>
#include "common.hpp"
#include "Settings.hpp"
#include "json.hpp"

namespace splineengine {

const int defaultAnchorsNb = 5;
const float defaultSegmentLength = 5.f;

//how much unexpected turns there are in the spline ? 0: a lot, +infinity : none 
const float splineSmoothness = 1.2f;

// delta position used to rotate the camera and the objects facing the curve
// it is large in order to have smooth camera movements
const float deltaSpline = 0.1f;

// the camera always looks a bit down
const float lookDownAngle = 0.3f;
// the higher the camera is, the lower it looks on the spline following this factor
const float lookDownFactor = -0.02f;
// camera focus point is a bit ahead of the plane
const float camLead = 0.0f;


/// \brief Represents the spline, its equation and transforms
class Spline {
    // METHODS
    public:
        // CONSTRUCTORS - DESTRUCTORS
        /// \brief default random spline constructor spline with "defaultAnchorsNb" anchors
        Spline();

        /// \brief random spline constructor with given number of anchors

        /// \brief spline constructor from level name (loads json)
        Spline(const std::string& levelName);

        /// \brief spline Destructor
        ~Spline()
        {};

        // CONST GETTERS
        // none for now
        
        // NON-CONST GETTERS (can be used as setters)
        // none for now
        std::vector<glm::vec3> anchors() { return _anchors; };

        // METHODS
        /// \brief evaluate the spline at the forward coordinate t and returns the world-space vec3 point corresponding
        glm::vec3 point(const float t) const;

        /// \brief returns the transforma matrix for the camera at the given point
        glm::mat4 camMatrix(const glm::vec3& sPoint) const;
        
        /// \brief returns the transforma matrix for an object the given point
        glm::mat4 matrix(const glm::vec3& sPoint) const;

        /// \brief length of the actual spline
        float length() const { return _segmentLength * (_anchors.size() - 3); }
        
        /// \brief add a random anchor to the end of the spline
        void addAnchor();
        /// \brief add a given to the end of the spline
        void addAnchor(const glm::vec3& anchor);

    protected:
        void loadFromLevel(const std::string& levelName);
        /// \brief Returns a position between 4 Vector3 with Catmull-Rom spline algorithm
        /// \brief (when t goes between 0-1, position goes between p1-p2. p0, p3 are just control points)
        glm::vec3 getCatmullRomPosition(
            const float t,
            const glm::vec3& p0,
            const glm::vec3& p1,
            const glm::vec3& p2,
            const glm::vec3& p3) const;
    // MEMBERS        
        
        // TODO : make spline from list of vec3
        std::vector<glm::vec3> _anchors;
        // length of a segment between 2 anchors
        float _segmentLength;
};        
}
#endif