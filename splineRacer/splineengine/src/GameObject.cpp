#include <glimac/SDLWindowManager.hpp>
#include <glimac/Geometry.hpp>
#include <splineengine/GameObject.hpp>


namespace splineengine {

GameObject::GameObject (
    const Model& model, const Spline& spline, const bool isStatic,
    const glm::vec3& sPosition, const glm::vec3& scale, const glm::vec3& rotation
)
    :_model(model), _spline(spline), _isStatic(isStatic),
    _sPosition(sPosition), _scale(scale), _rotation(rotation)
{
    // std::cout << "GameObject constructor " << std::endl;
};

GameObject::GameObject(const GameObject& g)
    :_model(g._model), _spline(g._spline), _isStatic(g._isStatic),
    _sPosition(g._sPosition), _scale(g._scale), _rotation(g._rotation)
{};

const glm::mat4 GameObject::matrix() {
    if (_isStatic && _hasMatrix) {
        return _transformMat;
    }
    
    glm::mat4 objMatrix = _spline.matrix(_sPosition);
    objMatrix = glm::scale(objMatrix, _scale);
    objMatrix = glm::rotate(objMatrix, _rotation[FWD],  -fwdVec);
    objMatrix = glm::rotate(objMatrix, _rotation[LEFT], -leftVec);
    objMatrix = glm::rotate(objMatrix, _rotation[UP],   -upVec);
    
    if (_isStatic) {
        _transformMat = objMatrix;
        _hasMatrix = true;
    }
    return objMatrix;
}


bool GameObject::intersect(GameObject& other) {
    if (
        _model.collider().intersect(
            other._model.collider(), //other collider
            matrix(),  //self transform matrix
            (_scale.x + _scale.y + _scale.z) / 3.f, // self scale
            other.matrix(), //other transform matrix
            (other._scale.x + other._scale.y + other._scale.z) / 3.f // other scale
        )
    ) {
        return true;
    }
    return false;
}

void GameObject::collideWith(GameObject& other) {
    if (intersect(other)) {
        doCollisionWith(other);
        other.doCollisionWith(*this);
    }
}

void GameObject::draw() const {
    glBindTexture(GL_TEXTURE_2D, _model.textureID());
    glBindVertexArray(_model.VAO());
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _model.IBO());
    glDrawElements(GL_TRIANGLES, _model.geometry().getIndexCount(), GL_UNSIGNED_INT, 0); // Draw all meshes
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

}