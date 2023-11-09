#pragma once

#include <random>
#include <chrono>

#include "pathtracingutil.hpp"
#include "interval.hpp"


class Random
{
public:
	static inline double get_rand_double(int seed = std::chrono::system_clock::now().time_since_epoch().count()) {
		static std::mt19937 gen(seed);
		static std::uniform_real_distribution<> dis(0.0, 1.0);
		return dis(gen);
	}
	static inline double get_rand_double(double min, double max, int seed = std::chrono::system_clock::now().time_since_epoch().count()) {
		static std::mt19937 gen(seed);
		static std::uniform_real_distribution<> dis(min, max);
		return dis(gen);
	}
};

