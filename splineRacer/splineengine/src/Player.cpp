#include <cmath>
#include <vector>
#include <iostream>
#include "glimac/common.hpp"
#include "splineengine/Player.hpp"

namespace splineengine {

void Player::updateSpeed(const float dt) {
	// component-wise linear interpolation of the speed toward it's speed target (_sMaxSpeed * _sInput)
	_sSpeed = glm::mix(_sSpeed, _sMaxSpeed * _sInput, _sAcceleration * dt);
}

void Player::updatePosition(const float dt) {
	_sPosition += _sSpeed * dt;
}

void Player::update(const float dt) {
	_sInput[LEFT] = glm::clamp(_sInput[LEFT], -1.f, 1.f);
	_sInput[UP] = glm::clamp(_sInput[UP], -1.f, 1.f);
	updateSpeed(dt);	
	updatePosition(dt);	
}

}
