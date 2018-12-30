// #pragma once
// #ifndef __SKYBOX__HPP
// #define __SKYBOX__HPP
//
// #include <iostream>
// #include "common.hpp"
// #include "Model.hpp"
//
//
// namespace splineengine{
// class Skybox{
// public:
//
//   Skybox(
//     const Model& model
//   );
//
//   ~Skybox();
//
//   void draw();
//
//   const glm::vec3& sPosition() const { return _sPosition; }
//
//   /// \brief Get the rotation of the object as aconst reference
//   const glm::vec3& rotation() const { return _rotation; }
//
//   /// \brief Get the scale of the object as a const reference
//   const glm::vec3& scale() const { return _scale; }
//
//   /// \brief Get the model of the object as a const reference
//   const Model& model() const { return _model; }
//
// private:
//   const Model& _model;
//
//   glm::vec3 _sPosition;
//   glm::vec3 _scale;
//   glm::vec3 _rotation;
//
//
// };
//
//
//
//
// }
//
// #endif
