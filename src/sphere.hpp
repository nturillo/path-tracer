#pragma once

#include "hittable.hpp"

class Sphere : public Hittable {
    public:
    Sphere() : center(), radius() {};
    Sphere(point3 _center, double _radius, shared_ptr<Material> _material) : center(_center), radius(_radius), material(_material) {};

    bool hit(const ray& r, const Interval& interval, Hit_Record& hr) const override {
        vec3 center_to_origin = r.get_origin() - center; //vec from circle center to ray origin

        //quadratic formula solve for t
        double a = r.get_direction().length_squared();
        double b_div_by_2 = dot(r.get_direction(), center_to_origin);
        double c = center_to_origin.length_squared() - radius * radius;
        
        double discr_div_by_4 = b_div_by_2 * b_div_by_2 - a * c;
        
        if (discr_div_by_4 < 0) return false; //no hits for t in the reals

        double discr_sqrt = sqrt(discr_div_by_4);
        double t = (-b_div_by_2 - discr_sqrt) / a;

        if (!interval.contains_closed(t)) {
            t = (-b_div_by_2 + discr_sqrt) / a;
            if (!interval.contains_closed(t)) return false; //no hits for t in [t_min, t_max]
        }

        point3 hit_point = r.at(t);
        vec3 hit_normal = hit_point - center;
        vec3 hit_normal_u = hit_normal / radius;
        
        hr.point = hit_point;
        hr.normal = hit_normal_u;
        hr.t = t;
        hr.set_face_normal(r, hit_normal);
        hr.material = this->material;

        return true;
    }

    private:
    shared_ptr<Material> material;
    point3 center;
    double radius;
};
