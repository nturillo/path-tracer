#pragma once

#include <iostream>

#include "pathtracingutil.hpp"
#include "vec3.hpp"

typedef vec3 Color; // RGB color

inline double linear_to_gamma(double x) {
    return sqrt(x);
}

inline int to_255(double x) {
    x = linear_to_gamma(x);
    Interval i(0.0, 1.0);
    x = i.clamp(x);
    return static_cast<int>(x >= 1.0 ? 255.0 : 256.0 * x);
}

inline void write_color(std::ostream& out, Color pixel_color) {
    out << to_255(pixel_color.x()) << ' '
        << to_255(pixel_color.y()) << ' '
        << to_255(pixel_color.z()) << '\n';
}
