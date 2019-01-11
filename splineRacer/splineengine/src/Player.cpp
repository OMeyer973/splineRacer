#include <cmath>
#include <vector>
#include <iostream>
#include "glimac/common.hpp"
#include "splineengine/Player.hpp"

namespace splineengine {

Player::Player(
    const GameObject& gameObject,
    const glm::vec3   maxSpeed,
    const glm::vec3   acceleration
)
    :GameObject(gameObject),
    _sSpeed(defaultPlayerMaxSpeed[FWD], 0.f, 0.f), // initial speed is only forward
    _sMaxSpeed(maxSpeed),
    _sAcceleration(acceleration),
    _sInput(1.f, 0.f, 0.f),
    _score(0)
{
	_music = Mix_LoadMUS("../splineRacer/assets/musics/coin.mp3");
}

void Player::updateSpeed(const float dt) {
	// linear interpolation of the speed toward it's speed target (_sMaxSpeed * _sInput)
	_sSpeed[FWD] = glm::mix(_sSpeed[FWD], _sMaxSpeed[FWD] * _sInput[FWD], _sAcceleration[FWD] * dt);
	_sSpeed[UP]  = glm::mix(_sSpeed[UP],  _sMaxSpeed[UP] *  _sInput[UP],  _sAcceleration[UP] * dt);

	// the higher you are, the slower you rotate
	_sSpeed[LEFT]  = glm::mix(_sSpeed[LEFT],  _sMaxSpeed[LEFT] *  _sInput[LEFT] / glm::max(_sPosition[UP],1.f),  _sAcceleration[LEFT] * dt);

	glm::clamp(_sSpeed, -defaultPlayerMaxSpeed, defaultPlayerMaxSpeed);
}

void Player::updatePosition(const float dt) {
	_sPosition += _sSpeed * dt;
	_sPosition[UP] = glm::clamp(_sPosition[UP], minPlayerUp, maxPlayerUp);

	// multiply by up position to counter the decrease in rotation speed
	_rotation = glm::vec3(_sSpeed[LEFT] * _sPosition[UP] * tiltFactor, _sSpeed[UP] * tiltFactor, 0);
}

void Player::update() {
	GameObject::update();
	const float dt = Settings::instance().deltaTime();
	_sInput[LEFT] = glm::clamp(_sInput[LEFT], -1.f, 1.f);
	_sInput[UP] = glm::clamp(_sInput[UP], -1.f, 1.f);
	updateSpeed(dt);
	updatePosition(dt);


	if (_collisionCooldownTimer > 0)
		_collisionCooldownTimer -= dt;

	_propellerRotationAngle -= propellerRotationSpeed;
}

void Player::doCollisionWith(GameObject& other) {
	if (debug) std::cout << "doing player collision behaviour with GameObject" << std::endl;
}

void Player::doCollisionWith(Obstacle& other) {
	if (debug) std::cout << "doing player collision behaviour with Obstacle : Bounce" << std::endl;

	// Bounce
	if (_collisionCooldownTimer <= 0) {
		_sSpeed = -_sSpeed * defaultPlayerBounceFactor;
		_collisionCooldownTimer = collisionCooldowd;
	}
}

void Player::doCollisionWith(Collectable& collectable) {
	if (!collectable.isTaken()) {
		//Mix_PauseMusic();
		_score+=100;
		//Mix_PlayMusic(_music,1);
		//Mix_VolumeMusic(MIX_MAX_VOLUME/2);
	}
}

void Player::doCollisionWith(Chaser& chaser) {
	_sMaxSpeed = glm::vec3(0);
}


void Player::draw(RenderManager &renderManager, Camera &camera) {
	glBindTexture(GL_TEXTURE_2D, _textureID);
	glBindVertexArray(_model.VAO());

	/* On boucle sur les meshs de l'object pour les afficher un par un et
	   appliquer des textures ou des tranformations différentes pour chaque mesh. */
	glm::mat4 MVMatrix;

	for (int i = 0; i < _model.geometry().getMeshCount(); ++i)
	{
		MVMatrix = renderManager.splineCamMatrix() * this->matrix();
		renderManager.updateMVMatrix(camera, MVMatrix, _scale);
		renderManager.useProgram(MULTI_LIGHT);

		const glimac::Geometry::Mesh* currentMesh = (_model.geometry().getMeshBuffer()+i);
		GLint indexCount = currentMesh->m_nIndexCount;
		GLint indexOffset = currentMesh->m_nIndexOffset;

		if (currentMesh->m_sName == "propeller") // Si le mesh courant correspond aux hélices
		{
			//TODO : fait des segfault chez olivier des fois (mais je crois que c'est des problèmes de compil local et de lib pt)
			MVMatrix = renderManager.splineCamMatrix() * glm::rotate(this->matrix(), _propellerRotationAngle, fwdVec);
			renderManager.updateMVMatrix(camera, MVMatrix, _scale);
			renderManager.useProgram(MULTI_LIGHT);
		}

		glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, (const GLvoid*) (indexOffset * sizeof(GLuint)));
	}

	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

}
