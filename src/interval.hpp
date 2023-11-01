#pragma once

#include <limits>

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

	static const Interval empty, R, positive, negative;
};

const Interval Interval::empty(std::numeric_limits<double>::infinity(), -std::numeric_limits<double>::infinity());
const Interval Interval::R(-std::numeric_limits<double>::infinity(), std::numeric_limits<double>::infinity());
const Interval Interval::positive(0, std::numeric_limits<double>::infinity());
const Interval Interval::negative(-std::numeric_limits<double>::infinity(), 0);