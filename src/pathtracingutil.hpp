#pragma once

#include <cmath>
#include <limits>
#include <memory>
#include <random>
#include <chrono>


// Usings

using std::shared_ptr;
using std::make_shared;
using std::sqrt;

// Constants

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// Random Number Generator
static std::mt19937_64 rng = std::mt19937_64(std::chrono::system_clock::now().time_since_epoch().count());

// Utility Functions

inline double degrees_to_radians(double degrees) {
    return degrees * pi / 180.0;
}
inline double get_random_double() {
    std::uniform_real_distribution<double> dist(0.0, 1.0);
    return dist(rng);
}
inline double get_random_double(double min, double max) {
	std::uniform_real_distribution<double> dist(min, max);
	return dist(rng);
}
inline double get_gaussian_double(double mean, double std_dev) {
	std::normal_distribution<double> dist(mean, std_dev);
	return dist(rng);
}

// Common Headers

#include "ray.hpp"
#include "vec3.hpp"
#include "interval.hpp"
#include "color.hpp"