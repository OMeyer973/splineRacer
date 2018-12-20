#include <splineengine/CubeMap.hpp>


namespace splineengine{

  CubeMap::CubeMap(std::string cubeFront, std::string cubeLeft,std::string cubeBack, std::string cubeBottom,std::string cubeRight, std::string cubeTop)
  : _id(0), _cubeImgFront(cubeFront),_cubeImgLeft(cubeLeft),
  _cubeImgBack(cubeBack), _cubeImgBottom(cubeBottom),
  _cubeImgRight(cubeRight), _cubeImgTop(cubeTop)
  {}

  bool CubeMap::loadCubeMapSide(GLenum target, const std::string cubeImg){
    int x, y;
   std::unique_ptr<glimac::Image> sideTexture = glimac::loadImage(cubeImg);
   x = sideTexture->getWidth();
   y = sideTexture->getHeight();

   // copy image data into 'target' side of cube map
   glTexImage2D( target,
                 0,
                 GL_RGBA,
                 sideTexture->getWidth(),
                 sideTexture->getHeight(),
                 0,
                 GL_RGBA,
                 GL_FLOAT,
                 sideTexture->getPixels()
               );

   return true;
  }


  bool CubeMap::loadCubeMap() {
    glActiveTexture(GL_TEXTURE0);
    glEnable(GL_TEXTURE_CUBE_MAP);
    glGenTextures(1, &_id);
    glBindTexture(GL_TEXTURE_CUBE_MAP, _id);

    // load each image and copy into a side of the cube-map texture
    CubeMap::loadCubeMapSide(GL_TEXTURE_CUBE_MAP_POSITIVE_X, _cubeImgFront);
    CubeMap::loadCubeMapSide(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, _cubeImgBack);
    CubeMap::loadCubeMapSide(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, _cubeImgTop);
    CubeMap::loadCubeMapSide(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, _cubeImgBottom);
    CubeMap::loadCubeMapSide(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, _cubeImgLeft);
    CubeMap::loadCubeMapSide(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, _cubeImgRight);

    // format cube map texture
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glDisable(GL_TEXTURE_CUBE_MAP);
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

    return true;
  }

}
