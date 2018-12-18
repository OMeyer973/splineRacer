#include <glimac/SDLWindowManager.hpp>
#include <splineengine/GameObject.hpp>


namespace splineengine {

glm::mat4 const GameObject::matrix(const Spline& spline) {
    glm::mat4 objMatrix = spline.matrix(_sPosition);
    objMatrix = glm::scale(objMatrix, _scale);
    objMatrix = glm::rotate(objMatrix, _rotation[FWD],  -fwdVec);
    objMatrix = glm::rotate(objMatrix, _rotation[LEFT], -leftVec);
    objMatrix = glm::rotate(objMatrix, _rotation[UP],   -upVec);
    return objMatrix;
}

}