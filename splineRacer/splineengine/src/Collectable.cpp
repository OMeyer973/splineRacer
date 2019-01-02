#include "glimac/common.hpp"
#include "splineengine/Collectable.hpp"
// #include <math.h>

namespace splineengine {

Collectable::Collectable(const GameObject& gameObject)
	:GameObject(gameObject), _isTaken(false), _isHidden(false)
{};

void Collectable::update(const float dt, const float pos, const glm::vec3 playerPos) {
	_rotation.z += collectableRotationSpeed*dt + pos/500;
	if (_isTaken && !_isHidden) {

		float collectableAngle = fmod(_sPosition[LEFT], (2.f*M_PI));
		if (collectableAngle < 0) {
			collectableAngle = (2 * M_PI) + collectableAngle;
		}

		float playerAngle = fmod(playerPos[LEFT], (2.f*M_PI));
		if (playerAngle < 0) {
			playerAngle = (2 * M_PI) + playerAngle;
		}

		if (((playerAngle > (2.f*M_PI) - .5f && collectableAngle < .5f)) || (playerAngle < .5f && collectableAngle > (2.f*M_PI) - .5f)) {
			collectableAngle = (2.f*M_PI) - collectableAngle;
		}


		_sPosition[FWD] = glm::mix(_sPosition[FWD], playerPos[FWD]+.25f, 1/4.f);
		_sPosition[UP] = glm::mix(_sPosition[UP], playerPos[UP], 1/4.f);
		_sPosition[LEFT] = glm::mix(collectableAngle, playerAngle, 1/3.f);
		_scale = glm::mix(_scale, glm::vec3(.5f), 1/8.f);

		if (_scale.x <= .6f)
		{
			_isHidden = true;
		}
	}
}

}
