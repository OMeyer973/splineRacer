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
// it's ok now :)
glm::mat4 Spline::camMatrix(const glm::vec3 sPoint) {

	// 4 tilt camera forward (the higher the camera is, the lower it looks on the spline)
	// TODO : this will probably go in the camera class
	glm::mat4 camMat = glm::rotate(glm::mat4(), lookDownFactor * sPoint[UP], glm::vec3(1,0,0));
	
	// 3 camera vertical distance to the spline (up-down)
	camMat = glm::translate(camMat, sPoint[UP] * glm::vec3(0,-1,0));

	// 2 camera rotation (left-right)
	camMat = glm::rotate(camMat, sPoint[LEFT], glm::vec3(0,0,-1));
	
	// 1 moving the camera forward and have it face toward the spline derivate
	camMat = camMat * glm::lookAt(point(sPoint[FWD]), point(sPoint[FWD]) + point(sPoint[FWD]+dx) - point(sPoint[FWD]-dx), glm::vec3(0,1,0));

	return camMat;

    // glm::mat4 transformMatrix;    
    // //camera part
    // //how far have we traveled on the spline ?

    // //std::cout << playerUpSpeed << std::endl; 

    // float delta = 0.3; //used to calculate a derivate

    // //translation of the camera folowing the spline
    // glm::vec3 worldPosition = point(sPoint[FWD]);

    
    // // calculating the 3 vectors of the spline reference
    // // used to rotate the camera -> face the direction of the spline

    // //using (0,1,0) as the reference for the up direction
    // glm::vec3 zS = glm::normalize(point(sPoint[FWD]-delta) - point(sPoint[FWD]+delta));
    // glm::vec3 xS = glm::normalize(glm::cross(glm::vec3(0,1,0), zS));
    // glm::vec3 yS = glm::normalize(glm::cross(-zS, xS));
    
    // //using the curvature of the spline  as the up direction --> makes buggy code
    // // glm::vec3 zS = glm::normalize(spline.point(camProgress+delta) - spline.point(camProgress));
    // // glm::vec3 xS = glm::normalize(glm::cross(spline.point(camProgress) - spline.point(camProgress-delta), zS));
    // // glm::vec3 yS = glm::normalize(glm::cross(zS, xS));

    // float splineRotContent[16] = {
    //     xS[0], yS[0], zS[0], 0,
    //     xS[1], yS[1], zS[1], 0,
    //     xS[2], yS[2], zS[2], 0,
    //     0    , 0    , 0    , 1};

    // glm::mat4 splineRotMat = glm::make_mat4(splineRotContent);

    // // 4 offset to hover above the spline
    // transformMatrix = glm::translate(transformMatrix, glm::vec3(
    //     -sPoint[UP]*yS[0],
    //     -sPoint[UP]*yS[1],
    //     -sPoint[UP]*yS[2]));

    // // 3 rotation around the curve part (player left-right)
    // transformMatrix = glm::rotate(transformMatrix, sPoint[LEFT], zS);

    // // 2 translate to the camera position on the spline
    // transformMatrix = glm::translate(transformMatrix, -worldPosition);

    // // 1 rotate to face the spline
    // transformMatrix = splineRotMat * transformMatrix;

    // return transformMatrix;
}

// TODO
glm::mat4 Spline::matrix(const glm::vec3 sPoint) {
	
	glm::mat4 objMat = glm::inverse(glm::lookAt(point(sPoint[FWD]), point(sPoint[FWD]+dx), glm::vec3(0,1,0)));
	
	objMat = glm::rotate(objMat, -sPoint[LEFT], glm::vec3(0,0,1));

	objMat = glm::translate(objMat, -sPoint[UP] * glm::vec3(0,1,0));

	return objMat;

	// don't work good anymore since lookDownFactor was introduces
	// return glm::inverse(camMatrix(sPoint));


}


}


