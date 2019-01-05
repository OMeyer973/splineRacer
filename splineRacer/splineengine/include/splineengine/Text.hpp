// #pragma once
// #ifndef __TEXT__HP
// #define __TEXT__HP
//
// #include <iostream>
// #include "common.hpp"
// #include <fstream>
// #include <glimac/glm.hpp>
// #include <GL/gl.h>
// #include <map>
//
// #include <ft2build.h>
// #include FT_FREETYPE_H
//
// namespace splineengine{
//
//
// struct Glyph
// {
//   GLuint _textureID;   // ID handle of the glyph texture
//   glm::ivec2 _size;    // Size of glyph
//   glm::ivec2 _bearing; // Offset from baseline to left/top of glyph
//   GLuint _advance;     // Offset to advance to next glyph
// };
//
// /**
//  * @brief Load, add and display scores
//  *
//  */
// class Text
// {
// public:
//   // ================ METHODS ==============
//   void setupTTF();
//   void renderText(const std::string &text, const GLfloat &x, const GLfloat &y, const GLfloat &scale, const glm::vec3 &color);
//
// private:
//   std::map<GLchar, Glyph> _glyphes;
//   GLuint _vbo, _vao;
// };
//
// }
//
// #endif
