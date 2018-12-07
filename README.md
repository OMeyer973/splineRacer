# splineRacer
IMAC semester 3 C++ and openGL 3 project. temple run clone but about a plane flying around a spline.

#### Install project
```shell
mkdir splineRacer-build
cd splineRacer-build
cmake ../SplineRacer
make
./PATH/TO/EXECUTABLE
```

<<<<<<< HEAD
## Coding norms

- all variables must be in lowerCamelCase
```c++
int myVariable = 1;
```

- Class must have both pragma once and indef..define..endif
- Class names must be in UpperCamelCase
- Class members must be protected and start with _ 

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




## Inspirations and references

- [Proun](http://www.proun-game.com)
- [Tail Drift](https://store.steampowered.com/app/330520/Tail_Drift/)

#### References
- [Catmull Rom spline reference](https://en.wikipedia.org/wiki/Cubic_Hermite_spline)