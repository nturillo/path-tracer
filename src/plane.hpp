#pragma once

#include "pathtracingutil.hpp"
#include "hittable.hpp"
#include "hit_record.hpp"

class Plane : public Hittable {
public:
	point3 origin = point3(0, 0, 0);
	vec3 normal = vec3(0, 1, 0);
	shared_ptr<Material> material = nullptr;

	Plane(const point3& origin, const vec3& normal, shared_ptr<Material> material) : origin(origin), normal(normal), material(material) {}

	bool hit(const ray& r, const Interval& interval, Hit_Record& hr) const override {
		double x = dot(r.get_direction(), normal);
		if (std::abs(x) < 1e-8) {
			return false;
		}
		double y = dot(origin - r.get_origin(), normal);
		double t = y / x;

		
		if (!interval.contains_closed(t)) {
			return false;
		}

		hr.t = t;
		hr.point = r.at(t);
		hr.set_face_normal(r, normal);
		hr.material = material;

		return true;
	}
};