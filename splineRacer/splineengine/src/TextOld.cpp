// #include "splineengine/Text.hpp"
//
// namespace splineengine{
//
//
// Text::Text(){
//   _plane = glimac::Plane();
//   _planeVBO = _plane.getVBO();
//   _planeIBO = _plane.getIBO();
//   _planeVAO = _plane.getVAO(&_planeIBO, &_planeVBO);
// }
//
// void Text::initText(){
//   if (TTF_Init() < 0) {
//       std::cout << "SDL_TTF library could not be load" << std::endl;
//   }
// }
//
// TTF_Font* Text::loadFont(const char* fontfile){
//   TTF_Font* font = TTF_OpenFont(fontfile, 48);
//     if (font == NULL)
//     {
//       TTF_SetError("Loading failed :( (code: %d)", 142);
//       std::cout << "Error: " << TTF_GetError() << std::endl;
//       return NULL;
//     }
//     return font;
// }
//
// void Text::clean(){
//     TTF_Quit();
// }
//
// // void loadFont()
// // {
// //   //font = Text::loadFont("../assets/fonts/Roboto-Bold.ttf");
// // }
// //
//
//
// //
// //
// // SDL_Surface* Text::createTextTexture(GLuint* textImg, std::string text, SDL_Color color)
// // {
// //   // m_plane = Plane();
// //   // m_planeVBO = m_plane.getVBO();
// //   // m_planeIBO = m_plane.getIBO();
// //   // m_planeVAO = m_plane.getVAO(&m_planeIBO, &m_planeVBO);
// //
// //   _surface = SDL_DisplayFormatAlpha(TTF_RenderUTF8_Solid( _font, text.data(), color ));
// //   int colors =  _surface->format->BytesPerPixel;
// //   SDL_Rect area;
// //   area.x = 0; area.y = 0; area.w = _surface->w; area.h = _surface->h;
// //   GLenum texture_format = GL_RGBA;
// //
// //   glDisable(GL_TEXTURE);
// //   glDisable(GL_TEXTURE_2D);
// //   glEnable(GL_BLEND);
// //   glBlendFunc(GL_SRC_COLOR, GL_ONE_MINUS_SRC_ALPHA);
// //   GLuint img;
// //
// //   glGenTextures(1, &img);
// //   glBindTexture(GL_TEXTURE_2D, img);
// //   glTexImage2D( GL_TEXTURE_2D,
// //                 0,
// //                 colors,
// //                 _surface->w,
// //                 _surface->h,
// //                 0,
// //                 texture_format,
// //                 GL_UNSIGNED_BYTE,
// //                 _surface->pixels
// //               );
// //   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
// //   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
// //   glBindTexture(GL_TEXTURE_2D, 0);
// //   glDisable(GL_BLEND);
// //   *textImg = img;
// //
// //   return _surface;
// // }
// //
// // void Text::drawText(SDL_Surface* textSurface, GLuint textImg, float size, float x, float y)
// // {
// //   // _renderManager.useProgram(TEXTURE);
// //   // glBindVertexArray(m_planeVAO);
// //   // glm::mat4 matrix = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, -5.0f));
// //   // float ratio = floatDivision(textSurface->w, textSurface->h);
// //   // matrix = glm::scale(matrix, glm::vec3(size * ratio, size, 1.f));
// //   // //applyTransformations(TEXTURE, matrix);
// //   // glActiveTexture(GL_TEXTURE0);
// //   // glBindTexture(GL_TEXTURE_2D, textImg);
// //   // glEnable(GL_BLEND);
// //   // glEnable(GL_TEXTURE_2D);
// //   //
// //   // //disableTexture(TEXTURE, false);
// //   // glDisable(GL_TEXTURE_2D);
// //   // glDisable(GL_BLEND);
// //   // //debindVAO();
// // }
// // void Text::drawText(SDL_Surface* textSurface, GLuint textImg, float size, glm::mat4 matrix)
// // {
// //   //useProgram(TEXTURE);
// //   //bindPlaneVAO();
// //   // float ratio = floatDivision(textSurface->w, textSurface->h);
// //   // matrix = glm::scale(matrix, glm::vec3(size * ratio, size, 1.f));
// //   // //applyTransformations(TEXTURE, matrix);
// //   // glActiveTexture(GL_TEXTURE0);
// //   // glBindTexture(GL_TEXTURE_2D, textImg);
// //   // glEnable(GL_TEXTURE_2D);
// //   // //m_plane.drawPlane();
// //   // //disableTexture(TEXTURE, false);
// //   // glDisable(GL_TEXTURE_2D);
// //   //debindVAO();
// // }
//
//
//
// }
