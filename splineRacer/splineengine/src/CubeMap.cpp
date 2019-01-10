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
  }
