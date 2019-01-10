#include "splineengine/Spline.hpp"

#include <iostream>
#include <glm/gtc/noise.hpp>
#include <fstream>
#include "splineengine/Error.hpp"

namespace splineengine {


// CONSTRUCTORS
Spline::Spline()
	:_segmentLength(defaultSegmentLength)
{}


Spline::Spline(const std::string& levelName)
	:_segmentLength(defaultSegmentLength)
{
	// TODO THIS IS PLACEHOLDER UNTIL WE CAN LOAD A SPLINE FROM FILE
	 if (levelName == "Endless") {
		// first point : gives the general direction of the spline (random with y = 0)
		glm::vec3 tmpAnchor = glm::normalize(glm::abs(glm::sphericalRand(1.f)*glm::vec3(1.f,0.f,1.f)));
		_anchors.push_back(tmpAnchor);
	    for (size_t i=1; i<defaultAnchorsNb; ++i) {
	    	addAnchor();
	    }

	} else { 
		loadFromLevel(levelName);
	}
}

void Spline::loadFromLevel(const std::string& levelName) {
			std::string splinePath = Settings::instance().appPath().dirPath()
		+ ("../../splineRacer/assets/levels/" + levelName + ".spline");

	if (debug) std::cout << "loading spline from file : " << splinePath << std::endl;
	
	// TODO : check for exception
	std::ifstream splineStream(splinePath);

	if (splineStream.fail()) {
		throw(Error("tried to read invalid spline json file",__FILE__, __LINE__));
	}
	
	// cf https://github.com/nlohmann/json#examples
	nlohmann::json jsonSpline;
	splineStream >> jsonSpline;

	for (nlohmann::json::iterator it = jsonSpline.begin(); it != jsonSpline.end(); ++it) {
		_anchors.push_back(glm::vec3(
			(*it)["anchor_x"].get<float>(),
			(*it)["anchor_y"].get<float>(),
			(*it)["anchor_z"].get<float>()
		));
	}

}

void Spline::addAnchor() {
	float i = _anchors.size(); // id of the anchor we are going to add;
	glm::vec3 prevAnchor = _anchors.back();
	
	// random vec with x,y,z in -0.5,0.5
	glm::vec3 randomVec = glm::normalize(
		glm::abs(glm::sphericalRand(1.f))
	) - 0.5f * glm::vec3(1.f);

	randomVec = glm::normalize(splineSmoothness * glm::normalize(prevAnchor) + randomVec);
	//10 is the standard length between 2 anchors (can be changed with no effect on speed with defaultSegmentLength)
	prevAnchor += 10.f * randomVec;

	// glm::vec3 newVec = 100.f * (glm::vec3(
	// 	glm::perlin(glm::vec3(1+i*0.1f,0.f,0.f)),
	// 	glm::perlin(glm::vec3(0.f,i*0.1f,0.f)),
	// 	glm::perlin(glm::vec3(0.f,0.f,1+i*0.1f))
	// ));
	_anchors.push_back(prevAnchor);
}

void Spline::addAnchor(const glm::vec3& anchor) {
	_anchors.push_back(anchor);
}


glm::vec3 Spline::point(const float t) const {

	if (_anchors.size() < 4) {
		throw(Error("spline must have at least 4 anchors to call spline.point()",__FILE__, __LINE__));
	}

	double pos = t/_segmentLength;

	int i = (int)glm::floor(pos);
	float tmp = pos-(float)i;

	if (pos <= 0)
		return _segmentLength*glm::mix(_anchors[0], _anchors[1], pos+1);

	if (pos+3 >= _anchors.size())
		return _segmentLength*glm::mix(_anchors[_anchors.size()-2], _anchors[_anchors.size()-1], pos-_anchors.size()+3);

	const glm::vec3 p0 = _anchors[i];
	const glm::vec3 p1 = _anchors[i+1];
	const glm::vec3 p2 = _anchors[i+2];
	const glm::vec3 p3 = _anchors[i+3];

	return _segmentLength*getCatmullRomPosition(tmp, p0, p1, p2, p3);
}


// simple catmull-rom stolen from https://www.habrador.com/tutorials/interpolation/1-catmull-rom-splines/
glm::vec3 Spline::getCatmullRomPosition(
	const float t,
	const glm::vec3& p0,
	const glm::vec3& p1,
	const glm::vec3& p2,
	const glm::vec3& p3) const
{
	glm::vec3 a = 2.f * p1;
	glm::vec3 b = p2  - p0;
	glm::vec3 c = 2.f * p0  - 5.f * p1  + 4.f * p2 - p3;
	glm::vec3 d = -p0 + 3.f * p1  - 3.f * p2  + p3;

	//The cubic polynomial: a + b * t + c * t^2 + d * t^3
	glm::vec3 pos = 0.5f * (a + (b * t) + (c * t * t) + (d * t * t * t));

	return pos;
}

glm::mat4 Spline::camMatrix(const glm::vec3& sPoint) const {

	// 4 tilt camera forward (the higher the camera is, the lower it looks on the spline)
	// TODO : this will probably go in the camera class

	glm::mat4 camMat = glm::translate(glm::mat4(), fwdVec);

	camMat = glm::rotate(camMat, -lookDownAngle -lookDownFactor * sPoint[UP], leftVec);

	// 3 camera normal distance to the spline (up-down)
	camMat = glm::translate(camMat, -sPoint[UP] * upVec);

	// 2 camera rotation (left-right)
	camMat = glm::rotate(camMat, sPoint[LEFT], fwdVec);

	// 1 moving the camera forward and have it face toward the spline derivate
	float fwdPos = sPoint[FWD] - camLead;
	camMat = camMat * glm::lookAt(point(fwdPos), point(fwdPos) + point(fwdPos+deltaSpline) - point(fwdPos-deltaSpline), upVec);

	return camMat;
}

glm::mat4 Spline::matrix(const glm::vec3& sPoint) const {

	// 1 moving the object forward and have it face toward the spline derivate
	glm::mat4 objMat = glm::inverse(glm::lookAt(point(sPoint[FWD]), point(sPoint[FWD]+deltaSpline), upVec));

	// 2 object rotation (left-right)
	objMat = glm::rotate(objMat, -sPoint[LEFT], fwdVec);

	// 3 object normal distance to the spline (up-down)
	objMat = glm::translate(objMat, sPoint[UP] * upVec);

	return objMat;

	// don't work good anymore since lookDownFactor was introduces
	// return glm::inverse(camMatrix(sPoint));
}



// glm::mat4 Spline::camMatrix(const glm::vec3 sPoint) {
//     glm::mat4 transformMatrix;
//     //camera part
//     //how far have we traveled on the spline ?

//     //std::cout << playerUpSpeed << std::endl;

//     float delta = 0.3; //used to calculate a derivate

//     //translation of the camera folowing the spline
//     glm::vec3 worldPosition = point(sPoint[FWD]);


//     // calculating the 3 vectors of the spline reference
//     // used to rotate the camera -> face the direction of the spline

//     //using (0,1,0) as the reference for the up direction
//     glm::vec3 zS = glm::normalize(point(sPoint[FWD]-delta) - point(sPoint[FWD]+delta));
//     glm::vec3 xS = glm::normalize(glm::cross(glm::vec3(0,1,0), zS));
//     glm::vec3 yS = glm::normalize(glm::cross(-zS, xS));

//     //using the curvature of the spline  as the up direction --> makes buggy code
//     // glm::vec3 zS = glm::normalize(spline.point(camProgress+delta) - spline.point(camProgress));
//     // glm::vec3 xS = glm::normalize(glm::cross(spline.point(camProgress) - spline.point(camProgress-delta), zS));
//     // glm::vec3 yS = glm::normalize(glm::cross(zS, xS));

//     float splineRotContent[16] = {
//         xS[0], yS[0], zS[0], 0,
//         xS[1], yS[1], zS[1], 0,
//         xS[2], yS[2], zS[2], 0,
//         0    , 0    , 0    , 1};

//     glm::mat4 splineRotMat = glm::make_mat4(splineRotContent);

//     // 4 offset to hover above the spline
//     transformMatrix = glm::translate(transformMatrix, glm::vec3(
//         -sPoint[UP]*yS[0],
//         -sPoint[UP]*yS[1],
//         -sPoint[UP]*yS[2]));

//     // 3 rotation around the curve part (player left-right)
//     transformMatrix = glm::rotate(transformMatrix, sPoint[LEFT], zS);

//     // 2 translate to the camera position on the spline
//     transformMatrix = glm::translate(transformMatrix, -worldPosition);

//     // 1 rotate to face the spline
//     transformMatrix = splineRotMat * transformMatrix;

//     return transformMatrix;
// }


}
