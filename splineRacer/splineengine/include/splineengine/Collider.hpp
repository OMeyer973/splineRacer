#pragma once
#ifndef __COLLIDER__HPP
#define __COLLIDER__HPP

#include<vector>

namespace splineengine {

class Collider
{
	public:
		/// \brief Bounding box
		struct BBox {
		    glm::vec3 _min;
		    glm::vec3 _max;
		};

		Collider();
		~Collider();

	protected:
		std::vector<BBox> _Boxes;		
};

}
#endif