#pragma once

#include "pathtracingutil.hpp"
#include "hit_record.hpp"

class Material {
	public:
	virtual bool scatter(ray& ray, const Hit_Record& rec, Color& ray_color) const = 0; //responsible for setting ray and ray_color, determines if ray is scattered
};