#ifndef RAY_H
#define RAY_H

#include "vec3.hpp"

class ray {
    public:
        ray(): orig(), dir() {}
        ray(point3& origin, vec3& direction): orig(origin), dir(direction) {}

        point3 get_origin() const { return orig; }
        vec3 get_direction() const { return dir; }

        point3 at(double t) const {
            return orig + t * dir;
        }
    private:
        point3 orig;
        vec3 dir;
};

#endif