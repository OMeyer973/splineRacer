#include <cmath>
#include <vector>
#include <iostream>
#include "glimac/common.hpp"
#include "splineengine/Player.hpp"

namespace splineengine {

void Player::updateSpeed() {
	// component-wise linear interpolation of the speed toward it's speed target (_sMaxSpeed * _sInput)
	_sSpeed = glm::mix(_sSpeed, _sMaxSpeed * _sInput, _sAcceleration);
}

void Player::updatePosition() {
	_sPosition += _sSpeed;
}

void Player::update() {
	_sInput[LEFT] = glm::clamp(_sInput[LEFT], -1.f, 1.f);
	_sInput[UP] = glm::clamp(_sInput[UP], -1.f, 1.f);
	updateSpeed();	
	updatePosition();	
}

}
