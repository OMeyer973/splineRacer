#include <iostream>
#include <GL/glew.h>
#include "splineengine/Texture.hpp"
#include "splineengine/Settings.hpp"

namespace splineengine{

  Texture::Texture() : _texID(0), _texName("") {
  }


  //const glimac::Filepath &applicationPath,
  Texture::Texture(const std::string &textureName): _texID(0),_texName(textureName){
    //std::cout << "texture " << textureName << " created " << std::endl;
  }

  bool Texture::loadTexture(){
    glimac::FilePath texPath = Settings::instance().appPath().dirPath() + "../../splineRacer/assets/textures/" + _texName;

    _textureToLoad = loadImage(texPath);

    if ( _textureToLoad == NULL ) {
      // Throw exception
      std::cout << "Image " << _texName << " couldn't be loaded" << std::endl;
      return false;
    }

    glGenTextures(1, &_texID);
    glBindTexture(GL_TEXTURE_2D, _texID);
    glTexImage2D(GL_TEXTURE_2D,
              0,
              GL_RGBA,
              _textureToLoad->getWidth(),
              _textureToLoad->getHeight(),
              0,
              GL_RGBA,
              GL_FLOAT,
              _textureToLoad->getPixels());
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

    return true;
  }
}
