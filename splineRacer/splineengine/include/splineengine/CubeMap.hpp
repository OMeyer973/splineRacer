#pragma once
#ifndef __CUBE_MAP__HPP
#define __CUBE_MAP__HPP

#include <iostream>
#include <string>
#include "common.hpp"
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <glimac/Image.hpp>

namespace splineengine {

class CubeMap{
private:
  GLuint _id;

  std::string _cubeImgFront;
  std::string _cubeImgLeft;
  std::string _cubeImgBack;
  std::string _cubeImgBottom;
  std::string _cubeImgRight;
  std::string _cubeImgTop;

public:

  CubeMap(std::string cubeFront, std::string cubeLeft, std::string cubeBack,
               std::string cubeBottom, std::string cubeRight, std::string cubeTop);

  GLuint getID()const  {return _id;};
  ~CubeMap(){};


  bool loadCubeMapSide(GLenum target, const std::string cubeImg);
  bool loadCubeMap();

};

}

#endif
