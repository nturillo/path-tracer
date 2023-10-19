#ifndef COLOR_HPP
#define COLOR_HPP

#include <iostream>
#include "vec3.hpp"

typedef vec3 color; // RGB color

inline int to_255(double x) {
    return static_cast<int>(x >= 1.0 ? 255.0 : 256.0 * x);
}

void write_color(std::ostream& out, color pixel_color) {
    out << to_255(pixel_color.x()) << ' '
        << to_255(pixel_color.y()) << ' '
        << to_255(pixel_color.z()) << '\n';
}

#endif