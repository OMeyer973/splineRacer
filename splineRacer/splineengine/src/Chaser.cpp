#include "splineengine/Chaser.hpp"
#include "splineengine/Error.hpp"

namespace splineengine {

Chaser::Chaser(const GameObject& gameObject, const Player& player, const float delay)
	:GameObject(gameObject), _player(player)
{
	_sPosition[FWD] -= delay;
};


void Chaser::update() {
	const float t = Settings::instance().time();
	const float dt = Settings::instance().deltaTime();

    if (_chatchedPlayer) {
		_sPosition =  glm::mix(_sPosition, _player.sPosition(), chaserLateralSpeed);
    }

    else if (_chasingPlayer) {
	  	_sPosition[FWD] += glm::abs(_player.speed()[FWD]) * dt;
		_sPosition[UP] =  glm::mix(_sPosition[UP], _player.sPosition()[UP], chaserLateralSpeed);
		_sPosition[LEFT] = glm::mix(_sPosition[LEFT], _player.sPosition()[LEFT], chaserLateralSpeed); // TODO: this line create segfaults idk why ??

		_rotation[UP] += chaserRotateSpeed * dt;
		_rotation[FWD] = chaserWiggleAmp * glm::sin(chaserWiggleFreq * t);    	
    }
}

/// \brief trigger collision behavior when colliding with another Gameobjects.
void Chaser::doCollisionWith(Player& other) {
	_chatchedPlayer = true;
};


}
