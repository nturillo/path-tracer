#pragma once

#include <limits>
#include <algorithm>

struct Interval {
	double min;
	double max;
	
	Interval() : min(std::numeric_limits<double>::infinity()), max(-std::numeric_limits<double>::infinity()) {};
	Interval(double _min, double _max) : min(_min), max(_max) {};

	bool contains_closed(double t) const {
		return (t >= min) && (t <= max);
	}
	bool contains_open(double t) const {
		return (t > min) && (t < max);
	}
	double clamp(double t) const {
		return std::max(min, std::min(max, t));
	}

	static const Interval empty, R, positive, negative;
};

