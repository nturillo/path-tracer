#include <iostream> 
#include <cfloat>
#include <fstream>

#include "pathtracingutil.hpp"
#include "sphere.hpp"
#include "hittable_collection.hpp"
#include "camera.hpp"



bool hit_sphere(const point3& center, double radius, const ray& r) {
    vec3 oc = center - r.get_origin();
    double a = r.get_direction().length_squared();
    double b = 2.0 * dot(oc, r.get_direction());
    double c = oc.length_squared() - radius * radius;
    double discriminant = b * b - 4 * a * c;
    return (discriminant > 0);
}


int main() {
    //output
    std::string output_path = "image_output/test_image.ppm";
    auto output = std::ofstream(output_path);

    //camera
    Camera cam = Camera(Camera::CameraPreset::Standard, point3(0, 0, 0), vec3(0, 0, -1));
    cam.samples_per_pixel = 20;

    //spheres and objects
    Hittable_Collection world;
    auto sphere1 = make_shared<Sphere>(point3(-0.5, 0, -2), 0.5);

    world.add(sphere1);
    world.add(make_shared<Sphere>(point3(0, -2.5, -3), 2));
    world.add(make_shared<Sphere>(point3(2, 1, -10), 1));
  

    //Render image:
    cam.render(world, output);
}