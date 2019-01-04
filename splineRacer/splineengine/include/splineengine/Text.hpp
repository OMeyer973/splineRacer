#pragma once
#ifndef __TEXT__HPP
#define __TEXT__HPP
#include <SDL/SDL_ttf.h>
#include <string>
#include <iostream>
#include <glm/glm.hpp>
#include "RenderManager.hpp"
#include <glimac/Plane.hpp>

#include <GL/gl.h>
#include <freetype2/include/ft2build.h>

#include FT_FREETYPE_H

namespace splineengine{

class Text{
public:


  void loadFont();

  SDL_Surface* createTextTexture(GLuint* textImg, std::string text, SDL_Color color);


  void drawText(SDL_Surface* textSurface, GLuint textImg, float size, float x, float y);
  void drawText(SDL_Surface* textSurface, GLuint textImg, float size, glm::mat4 matrix);
  void initText();

  TTF_Font* loadFont(const char* fontfile);

  void clean();

private:
	RenderManager _renderManager;
  TTF_Font* _font;
  SDL_Surface* _surface;
  GLuint _text;

  //Plane m_plane;
  GLuint m_planeVBO;
  GLuint m_planeIBO;
  GLuint m_planeVAO;

};


}



#endif
