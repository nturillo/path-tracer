#include "interval.hpp"

const Interval Interval::empty(std::numeric_limits<double>::infinity(), -std::numeric_limits<double>::infinity());
const Interval Interval::R(-std::numeric_limits<double>::infinity(), std::numeric_limits<double>::infinity());
const Interval Interval::positive(0, std::numeric_limits<double>::infinity());
const Interval Interval::negative(-std::numeric_limits<double>::infinity(), 0);