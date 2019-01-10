#include "splineengine/Decoration.hpp"

namespace splineengine {

Decoration::Decoration(const GameObject& gameObject)
	:GameObject(gameObject)
{
	_isStatic = true;
	_rotation[FWD] = -_sPosition[LEFT];
};

}
