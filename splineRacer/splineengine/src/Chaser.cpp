#include "splineengine/Chaser.hpp"
#include "splineengine/Error.hpp"

namespace splineengine {

Chaser::Chaser(const GameObject& gameObject, const Player& player, const float delay)
	:GameObject(gameObject), _player(player)
{
	_sPosition[FWD] -= delay;
};


void Chaser::update(const float dt) {
    _sPosition[FWD] += glm::abs(_player.speed()[FWD]) * dt;
	_sPosition[UP] =  glm::mix(_sPosition[UP], _player.sPosition()[UP], chaserLateralSpeed);
	_sPosition[LEFT] = glm::mix(_sPosition[LEFT], _player.sPosition()[LEFT], chaserLateralSpeed); // TODO: this line create segfaults idk why ??

	_rotation[UP] += chaserRotateSpeed;
	_rotation[FWD] = chaserWiggleAmp * glm::sin(chaserWiggleFreq * _rotation[UP]);


// const float chaserRotateSpeed = 3.f;
// const float chaserWiggleAmp = 3.f;
// const float chaserWiggleFreq = 3.f;
}

/// \brief trigger collision behavior when colliding with another Gameobjects. 
void Chaser::doCollisionWith(Player& other) {
};


}
