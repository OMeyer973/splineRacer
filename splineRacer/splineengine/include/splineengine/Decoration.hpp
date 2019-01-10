#pragma once
#ifndef __DECORATION__HPP
#define __DECORATION__HPP

#include "GameObject.hpp"

namespace splineengine {

/// \brief Represents a Decoration Gameobject
class Decoration : public GameObject {
    // METHODS
    public:
    	/// \brief Decoration Constructor
    	Decoration(const GameObject& gameObject = GameObject(Model(), Spline(),"default.png", true));

    	/// \brief Decoration Destructor
    	~Decoration()
    	{};
};

}

#endif
