#pragma once
#ifndef __COMMON__HPP
#define __COMMON__HPP

#include <GL/glew.h>
#include<glm/gtc/random.hpp>
#include <glm/gtc/noise.hpp>

// declare global variables here

// directions for spline-space vectors
const int FWD = 0;
const int LEFT = 1; 
const int UP = 2;

// spline-space vectors
const glm::vec3 sFwdVec  (1.f,0.f,0.f);
const glm::vec3 sLeftVec (0.f,1.f,0.f);
const glm::vec3 sUpVec   (0.f,0.f,1.f);


#endif