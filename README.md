# splineRacer
IMAC semester 3 C++ and openGL 3 project. temple run clone but about a plane flying around a spline.

[![Splineracer demo](https://img.youtube.com/vi/6p8Vq_vyp4g/0.jpg)](https://www.youtube.com/watch?v=6p8Vq_vyp4g)

[see demo video](https://youtu.be/6p8Vq_vyp4g)

## Install project
```shell
mkdir splineRacer-build
cd splineRacer-build
cmake ../splineRacer
make
./src/SPLINERACER
```

## Game engine features
- Analogic movement in spline-space : rotate around the spline - X-axis: radial angle, Y-axis: radial distance
- World-space spheric collisions
- transform animation of objects
- optimised render and physics - far away objects are not computed

## Inspirations and references

#### Games inspirations
- [Proun](http://www.proun-game.com)
- [Tail Drift](https://store.steampowered.com/app/330520/Tail_Drift/)

#### References
- [Catmull Rom spline reference](https://en.wikipedia.org/wiki/Cubic_Hermite_spline)
- [ogldev opengl tutorials](http://ogldev.atspace.co.uk/)

## Libraries used
- tinyObjLoader
- Json for modern c++
- SDL_mixer
- FreeType

## Possible optimisations
- less collision detection: sort colliders in a octo-tree like hierarchy

## Coding norms
- all variables must be in lowerCamelCase
```c++
int myVariable = 1;
```

- Class must have both pragma once and indef..define..endif
- Class names must be in UpperCamelCase
- Class members must be protected and have an underscore as prefix ("\_")

```c++
#pragma once
#ifndef __MYCLASS__HPP
#define __MYCLASS__HPP

class MyClass {
	protected:
    int _myVariable = 1;
}
#endif
```

- Comments must be written in english as much as possible
- Don't forget to use Doxigen syntax when commenting your classes !


