#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "hittable.hpp"

class Sphere : Hittable {
    public:
    Sphere() : center(), radius() {};
    Sphere(point3 _center, double _radius) : center(_center), radius(_radius) {};

    bool hit(const ray& r, double t_min, double t_max, hit_record& hr) const override {
        vec3 center_to_origin = r.get_origin() - center; //vec from circle center to ray origin

        //quadratic formula solve for t
        double a = r.get_direction().length_squared();
        double b_div_by_2 = 2 * dot(r.get_direction(), center_to_origin);
        double c = center_to_origin.length_squared() - radius * radius;
        
        double discr_div_by_4 = b_div_by_2 * b_div_by_2 - 4 * a * c;
        
        if (discr_div_by_4 < 0) return false; //no hits for t in the reals

        double discr_sqrt = sqrt(discr_div_by_4);
        double t = (-b_div_by_2 - discr_sqrt) / a;

        if (t < t_min || t > t_max) {
            t = (-b_div_by_2 + discr_sqrt) / a;
            if (t < t_min && t > t_max) return false; //no hits for t in [t_min, t_max]
        }

        point3 hit_point = r.at(t);
        vec3 hit_normal = (hit_point - center) / radius;
        
        hr.point = hit_point;
        hr.normal = hit_normal;
        hr.t = t;
        //hr.set_face_normal(r, hit_normal);

        return true;
    }

    private:
    point3 center;
    double radius;
};

#endif