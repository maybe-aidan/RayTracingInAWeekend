#ifndef RAY_H
#define RAY_H

#include "rtweekend.h"

// Ray can be thought of as a the function:
// P(t) = A + tb
// Where: P is the *position* along a line in 3D
//		  A is the ray *origin*
//		  b is the ray *direction*
//
//     t = -1      t = 0        t = 1
//  <----|-----------+------------>------>
//                   A            B
// 
//     Example of linear interpolation

class ray {
public:
	ray(){}
	ray(const point3& origin, const vec3& direction) : orig(origin), dir(direction) {}

	const point3& origin() const { return orig; }
	const vec3& direction() const { return dir; }

	point3 at(double t) const {
		return orig + (t * dir);
	}

private:
	point3 orig;
	vec3 dir;
};

#endif
