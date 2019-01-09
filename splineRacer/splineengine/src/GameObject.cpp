#include <splineengine/GameObject.hpp>


namespace splineengine {

GameObject::GameObject (
        const Model& model,
        const Spline& spline,
        const std::string& textureName,
        const bool isStatic,
        const Transform& transform,
        //const uint animId
        const AnimationList& animations
    )
    :_model(model), _spline(spline),_isStatic(isStatic),
    _sPosition(transform._sPosition), _scale(transform._scale), _rotation(transform._rotation),
    _animations(std::move(animations))
{
    if (_animations.size() > 0 && _isStatic == true) {
        std::cerr << "warning : object declared as static but constructor has been callen with animations ids" << std::endl;
        std::cerr << "  -> object will not move." << std::endl;
    }
    // Texture
    setTexture(textureName);
};


void GameObject::addAnimation(uint animId) {
    _animations.emplace_back(3);
}

GameObject::GameObject(const GameObject& g)
    :_model(g._model),
    _spline(g._spline),
    _textureID(g._textureID),
    _isStatic(g._isStatic),
    _sPosition(g._sPosition),
    _scale(g._scale),
    _rotation(g._rotation),
    _animations(std::move(g._animations)) // list copy
{
};

const glm::mat4 GameObject::matrix() {
    if (_isStatic && _hasMatrix) {
        return _transformMat;
    }

    glm::mat4 objMatrix = _spline.matrix(_sPosition);
    // objMatrix = glm::scale(objMatrix, _scale);
    objMatrix = glm::rotate(objMatrix, _rotation[FWD],  -fwdVec);
    objMatrix = glm::rotate(objMatrix, _rotation[LEFT], -leftVec);
    objMatrix = glm::rotate(objMatrix, _rotation[UP],   -upVec);

    if (_isStatic) {
        _transformMat = objMatrix;
        _hasMatrix = true;
    }
    return objMatrix;
}

const glm::mat4 GameObject::staticMatrix() {
    if (_isStatic && _hasMatrix) {
        return _transformMat;
    }

    glm::mat4 objMatrix = glm::mat4();
    objMatrix = glm::translate(objMatrix, _sPosition);
    //objMatrix = glm::scale(objMatrix, _scale);
    objMatrix = glm::rotate(objMatrix, _rotation[FWD],  -fwdVec);
    objMatrix = glm::rotate(objMatrix, _rotation[LEFT], -leftVec);
    objMatrix = glm::rotate(objMatrix, _rotation[UP],   -upVec);

    if (_isStatic) {
        _transformMat = objMatrix;
        _hasMatrix = true;
    }

    return objMatrix;
}

void GameObject::update() {
    const float t = Settings::instance().time();
    const float dt = Settings::instance().deltaTime();
    if (_animations.size()>0)

    // if (debug) std::cout << "animations size" << _animations.size() << std::endl;
    for (AnimationList::const_iterator it = _animations.begin(); it != _animations.end(); ++it) {
        switch (*it) {
            case ROT_CONST_FWD :
                _rotation[FWD] += rotConstSpeed * dt;
                break;
            case ROT_CONST_LEFT :
                _rotation[LEFT] += rotConstSpeed * dt;
                break;
            case ROT_CONST_UP :
                _rotation[UP] += rotConstSpeed * dt;
                break;
            case MOVE_SIN_LEFT : //using += to take into acount the original position though Amplitude need to be adjusted (might be a bit off)
                _sPosition[LEFT] += moveSinAdjustedAmp * dt * (glm::sin(t * moveSinFreq * 2.f*M_PI));
                break;
            case MOVE_SIN_UP : //using += to take into acount the original position though Amplitude need to be adjusted (might be a bit off)
                _sPosition[UP] += moveSinAdjustedAmp * dt * (glm::sin(t * moveSinFreq * 2.f*M_PI));
                break;
            case MOVE_CONST_LEFT :
                _sPosition[LEFT] += moveConstSpeed * dt;
                break;
            case MOVE_CONST_RIGHT :
                _sPosition[LEFT] -= moveConstSpeed * dt;
                break;
            case MOVE_CONST_BACK :
                _sPosition[FWD] -= moveConstSpeed * dt;
                break;
            case MOVE_CONST_FWD :
                _sPosition[FWD] += moveConstSpeed * dt;
                break;
            case SCALE_SIN :
                _scale += scaleSinAdjustedAmp * dt * (glm::sin(t * scaleSinFreq * 2.f * M_PI));
                _scale = glm::abs(_scale);
                break;
        };
    }
}


void GameObject::draw() const {
    glBindTexture(GL_TEXTURE_2D, _textureID);
    glBindVertexArray(_model.VAO());
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _model.IBO());
    glDrawElements(GL_TRIANGLES, _model.geometry().getIndexCount(), GL_UNSIGNED_INT, 0); // Draw all meshes
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}


bool GameObject::intersect(GameObject& other) {
    float selfScale = (glm::abs(_scale.x) + glm::abs(_scale.y) + glm::abs(_scale.z)) / 3.f;
    float otherScale = (glm::abs(other._scale.x) + glm::abs(other._scale.y) + glm::abs(other._scale.z)) / 3.f;

    return (
        _model.collider().intersect(
            other._model.collider(), //other collider
            matrix(),  //self transform matrix
            selfScale, // self scale
            other.matrix(), //other transform matrix
            otherScale // other scale
        )
    );
}

void GameObject::collideWith(GameObject& other) {
    if (intersect(other)) {
        doCollisionWith(other);
        other.doCollisionWith(*this);
    }
}

void GameObject::setTexture(const std::string textureName) {
	AssetManager& assetManager = AssetManager::instance();
    std::map<std::string, Texture>::iterator itTexMap = assetManager.textures().find(textureName);
	// If texture already exists
	if (itTexMap !=  assetManager.textures().end()) {
		// Get it from AssetManager
		_textureID = itTexMap->second.getTextureID();
	} else { 
		// Create a new texture and add it to AssetManager
		Texture texture(textureName);
		_textureID = texture.getTextureID();
        assetManager.textures().insert(std::make_pair(textureName, texture));
	}
}

}
