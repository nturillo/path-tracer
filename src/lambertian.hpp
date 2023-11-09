#pragma once

#include "material.hpp"

class Lambertian : public Material {
public:
	Color albedo;
	
	Lambertian(const Color& a) : albedo(a) {}

	bool scatter(ray& r, const Hit_Record& rec, Color& ray_color) const override { //returns true if new ray is scattered
		vec3 scatter_direction = rec.normal + vec3::random_unit_vec();
		r = ray(rec.point, scatter_direction);
		ray_color = albedo * ray_color;
		return true;
	}
};