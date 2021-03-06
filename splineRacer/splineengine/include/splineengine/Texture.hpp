#pragma once
#ifndef __TEXTURE__HPP
#define __TEXTURE__HPP

#include <iostream>
#include <GL/glew.h>
#include <glimac/Geometry.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/Image.hpp>


namespace splineengine{

class Texture{
private:
	/// \  tableau de textures
	GLuint _texID;
	std::string _texName;
	std::unique_ptr<glimac::Image> _textureToLoad;

public:
	//Constructors
	// Default
	Texture();
	// Basic
	Texture(const std::string &textureName);
	// Copy
	Texture(const Texture& tex);

	// Destructor
	~Texture()
	{};
	
	// Getter
	GLuint getTextureID() const{ return _texID ; };

	//setter
	//void setTexture(const std::string &texture){ _texName = texture;  };

	

	bool loadTexture();

};

}

#endif
