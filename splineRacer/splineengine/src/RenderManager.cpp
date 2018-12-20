#include <splineengine/RenderManager.hpp>
#include <splineengine/Model.hpp>
namespace splineengine {

void RenderManager::updateMVMatrix(Camera &camera, glm::mat4 transformMatrix) {
    _MVMatrix = camera.getViewMatrix() * transformMatrix;
    _normalMatrix = glm::transpose(glm::inverse(_MVMatrix));

}

}
