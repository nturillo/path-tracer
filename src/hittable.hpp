#pragma once

#include "ray.hpp"
#include "vec3.hpp"
#include "interval.hpp"

class Hittable {
    public:
        struct Hit_Record {
            point3 point;
            vec3 normal;
            double t;
            bool front_face;

            Hit_Record() {
                point = point3();
                normal = vec3();
                t = 0.0;
                front_face = false;
            }

            Hit_Record(point3 _point, vec3 _normal, double _t, bool _front_face) {
                point = _point;
                normal = _normal;
                t = _t;
                front_face = _front_face;
            }

            inline void set_face_normal(const ray& r, const vec3& outward_normal) {
                front_face = dot(r.get_direction(), outward_normal) < 0;
                normal = front_face ? outward_normal : -outward_normal;
            }
        };


        virtual bool hit(const ray& r, const Interval& interval, Hit_Record& hr) const = 0;
};
