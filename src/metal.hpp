#pragma once

#include "pathtracingutil.hpp"
#include "material.hpp"

class Metal : public Material {
public:
	Color albedo = Color(0.8, 0.8, 0.8);
	double fuzz = 0.0;

	Metal() {};
	Metal(const Color& a) : albedo(a) {};
	Metal(const Color& a, double f) : albedo(a), fuzz(f) {};
	bool scatter(ray& r, const Hit_Record& rec, Color& ray_color) const override { //returns true if new ray is scattered
		vec3 scatter_direction = reflected_vec(r.get_direction(), rec.normal) + fuzz * vec3::random_unit_vec();
		r = ray(rec.point, scatter_direction);
		ray_color = albedo * ray_color;
		return (dot(scatter_direction, rec.normal) > 0);
	}
};