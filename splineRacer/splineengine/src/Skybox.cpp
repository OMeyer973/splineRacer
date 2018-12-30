// #include <splineengine/Skybox.hpp>
//
// namespace splineengine{
//
//   Skybox::Skybox():
//
//   {}
//
//
//   void Skybox::draw() const {
//       glBindTexture(GL_TEXTURE_2D, _model.textureID());
//       glBindVertexArray(_model.VAO());
//       // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _model.IBO());
//       glDrawElements(GL_TRIANGLES, _model.geometry().getIndexCount(), GL_UNSIGNED_INT, 0); // Draw all meshes
//       glBindVertexArray(0);
//       glBindTexture(GL_TEXTURE_2D, 0);
//   }
// }
