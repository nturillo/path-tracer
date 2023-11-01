#pragma once

#include "hittable.hpp"

#include <vector>
#include <memory>

using std::vector;
using std::shared_ptr;
using std::make_shared;

class Hittable_Collection :
    public Hittable
{
public:
 
    void add(shared_ptr<Hittable> ptr) {
        hittables.push_back(ptr);
    }
    void clear() {
        hittables.clear();
    }
    int size() {
        return hittables.size();
    }

    bool hit(const ray& r, const Interval& interval, Hit_Record& hr) const override {
        bool hit_anything = false;

        Hit_Record closest_hr;
        Interval search_interval = interval;

        for(auto const ptr : hittables) {
            if (ptr->hit(r, search_interval, closest_hr)) {
                //it's a hit!
                hit_anything = true;
                //adjust search interval to make sure we're not doing unnecessary searching
                search_interval.max = closest_hr.t;
            }
        }

        hr = closest_hr;
        return hit_anything;
    }
private:
    vector<shared_ptr<Hittable>> hittables;
};

