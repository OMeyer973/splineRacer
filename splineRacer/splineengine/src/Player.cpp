#include <cmath>
#include <vector>
#include <iostream>
#include "glimac/common.hpp"
#include "splineengine/Player.hpp"

namespace splineengine {

void Player::updatePosition() {
	//std::cout << _speed.fwd() << std::endl;
	_position.fwd() += _speed.fwd();
	_position.left() += _speed.left();
	_position.up() += _speed.up();
	//std::cout << _speed.fwd() << std::endl;

}

}
