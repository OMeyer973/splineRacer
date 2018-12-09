#include "splineengine/Spline.hpp"

namespace splineengine {

//tmp equation with perlin noise
glm::vec3 Spline::point(const float t) {
    return glm::vec3(
        t+30*glm::perlin(glm::vec2(0.1*t)), 
        t-30*glm::perlin(glm::vec2(-0.1*t)), 
        t+30*glm::perlin(glm::vec2(0.1*t+100))
    );
}

// TODO : CLEAN & OPTIMIZE THIS SHIT
glm::mat4 Spline::camMatrix(const glm::vec3 sPoint) {
    glm::mat4 transformMatrix;    
    //camera part
    //how far have we traveled on the spline ?

    //std::cout << playerUpSpeed << std::endl; 

    float delta = 0.3; //used to calculate a derivate

    //translation of the camera folowing the spline
    glm::vec3 worldPosition = point(sPoint[FWD]);

    
    // calculating the 3 vectors of the spline reference
    // used to rotate the camera -> face the direction of the spline

    //using (0,1,0) as the reference for the up direction
    glm::vec3 zS = glm::normalize(point(sPoint[FWD]-delta) - point(sPoint[FWD]+delta));
    glm::vec3 xS = glm::normalize(glm::cross(glm::vec3(0,1,0), zS));
    glm::vec3 yS = glm::normalize(glm::cross(-zS, xS));
    
    //using the curvature of the spline  as the up direction --> makes buggy code
    // glm::vec3 zS = glm::normalize(spline.point(camProgress+delta) - spline.point(camProgress));
    // glm::vec3 xS = glm::normalize(glm::cross(spline.point(camProgress) - spline.point(camProgress-delta), zS));
    // glm::vec3 yS = glm::normalize(glm::cross(zS, xS));

    float splineRotContent[16] = {
        xS[0], yS[0], zS[0], 0,
        xS[1], yS[1], zS[1], 0,
        xS[2], yS[2], zS[2], 0,
        0    , 0    , 0    , 1};

    glm::mat4 splineRotMat = glm::make_mat4(splineRotContent);

    // 4 offset to hover above the spline
    transformMatrix = glm::translate(transformMatrix, glm::vec3(
        -sPoint[UP]*yS[0],
        -sPoint[UP]*yS[1],
        -sPoint[UP]*yS[2]));

    // 3 rotation around the curve part (player left-right)
    transformMatrix = glm::rotate(transformMatrix, sPoint[LEFT], zS);

    // 2 translate to the camera position on the spline
    transformMatrix = glm::translate(transformMatrix, -worldPosition);

    // 1 rotate to face the spline
    transformMatrix = splineRotMat * transformMatrix;

    return transformMatrix;
}

// TODO
glm::mat4 Spline::matrix(const glm::vec3 sPoint) {
	    glm::mat4 transformMatrix;    
    //camera part
    //how far have we traveled on the spline ?

    //std::cout << playerUpSpeed << std::endl; 

    float delta = 0.3; //used to calculate a derivate

    //translation of the camera folowing the spline
    glm::vec3 worldPosition = point(sPoint[FWD]);

    ////////////
    // computing the 3 vectors of the spline reference
    // used to rotate the object -> face the direction of the spline

    //using (0,1,0) as the reference for the up direction
    glm::vec3 zS = glm::normalize(point(sPoint[FWD]-delta) - point(sPoint[FWD]+delta));
    glm::vec3 xS = glm::normalize(glm::cross(glm::vec3(0,1,0), zS));
    glm::vec3 yS = glm::normalize(glm::cross(-zS, xS));
    
    //using the curvature of the spline  as the up direction --> makes buggy code
    // glm::vec3 zS = glm::normalize(spline.point(camProgress+delta) - spline.point(camProgress));
    // glm::vec3 xS = glm::normalize(glm::cross(spline.point(camProgress) - spline.point(camProgress-delta), zS));
    // glm::vec3 yS = glm::normalize(glm::cross(zS, xS));

    float splineRotContent[16] = {
        xS[0], yS[0], zS[0], 0,
        xS[1], yS[1], zS[1], 0,
        xS[2], yS[2], zS[2], 0,
        0    , 0    , 0    , 1};

    glm::mat4 splineRotMat = glm::make_mat4(splineRotContent);
    ////////////

    // translate to the camera position on the spline
    transformMatrix = glm::translate(transformMatrix, worldPosition);
    
    // rotation around the curve part (player left-right)
    transformMatrix = glm::rotate(transformMatrix, sPoint[LEFT], zS);

    //offset to hover above the spline
    transformMatrix = glm::translate(transformMatrix, glm::vec3(
        -sPoint[UP]*yS[0],
        -sPoint[UP]*yS[1],
        -sPoint[UP]*yS[2]));


    // rotate to face the spline
     transformMatrix = transformMatrix / splineRotMat;
    

    return transformMatrix;
	// return glm::translate(glm::mat4(), point(sPoint[FWD]));	
}



}


