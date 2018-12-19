#include <iostream>
#include <GL/glew.h>
#include "splineengine/Texture.hpp"

namespace splineengine{

  Texture::Texture() : _texID(0), _texName("") {
  }


  //const glimac::Filepath &applicationPath,
  Texture::Texture(const std::string &textureName): _texID(0),_texName(textureName){
    std::cout << "texture " << textureName << " created " << std::endl;
  }

  bool Texture::loadTexture(const glimac::FilePath &applicationPath){
    std::cout << "texture " << _texName << "  pas encore  charged " << std::endl;

    glimac::FilePath texPath = applicationPath.dirPath() + "../../splineRacer/assets/textures/" + _texName;
    texPath = texPath.addExt(".png"); // Constructeur par copie
    //si texture nulle error

    _textureToLoad = loadImage(texPath);

    if ( _textureToLoad == NULL ){
      std::cout << "Image " << _texName << " couldn't be  Loaded" << std::endl;
      return false;
    }

      std::cout << "texture " << _texName << " c  harged " << std::endl;

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
