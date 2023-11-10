#pragma once

#include "pathtracingutil.hpp"
#include "ray.hpp"
#include "vec3.hpp"
#include "interval.hpp"
#include "material.hpp"
#include "hit_record.hpp"

class Material;

class Hittable {
    public:
        virtual bool hit(const ray& r, const Interval& interval, Hit_Record& hr) const = 0;
        //hit responsible for setting the following elements of hit_record: t, point, normal, material
};
