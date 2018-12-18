#include <glimac/SDLWindowManager.hpp>
#include <splineengine/GameObject.hpp>


namespace splineengine {

glm::mat4 const GameObject::matrix(Spline& spline) {
    glm::mat4 objMatrix = spline.matrix(_sPosition);
    objMatrix = glm::scale(objMatrix, _scale);
    objMatrix = glm::rotate(objMatrix, _rotation[FWD], sFwdVec);
    objMatrix = glm::rotate(objMatrix, _rotation[LEFT], sLeftVec);
    objMatrix = glm::rotate(objMatrix, _rotation[UP], sUpVec);
    return objMatrix;
}

}