#pragma once
#ifndef __TEXT__HPP
#define __TEXT__HPP

#include <iostream>
#include <glimac/common.hpp>
#include <fstream>
#include <glimac/glm.hpp>
#include <GL/gl.h>
#include <map>
#include <splineengine/common.hpp>
#include <splineengine/Settings.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H

namespace splineengine {

struct Glyph
{
	GLuint _textureID;   // ID handle of the glyph texture
	glm::ivec2 _size;    // Size of glyph
	glm::ivec2 _bearing; // Offset from baseline to left/top of glyph
	GLuint _advance;     // Offset to advance to next glyph
};

/**
 * @brief Load, add and display scores
 *
 */
class TextManager
{
public:
	// ================ METHODS ================
	void setupTTF();
	void renderText(const std::string &text, const GLfloat &x, const GLfloat &y, const GLfloat &scale, bool stickLetters = false);

private:
	std::map<GLchar, Glyph> _glyphes;
	GLuint _vbo, _vao;
};

}

#endif
