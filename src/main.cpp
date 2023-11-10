#include <iostream> 
#include <cfloat>
#include <fstream>

#include "pathtracingutil.hpp"
#include "sphere.hpp"
#include "hittable_collection.hpp"
#include "camera.hpp"
#include "material.hpp"
#include "lambertian.hpp"
#include "metal.hpp"



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
    cam.samples_per_pixel = 50;

    //spheres and objects
    Hittable_Collection world;
    Lambertian earth_mat = Lambertian(Color(0.3, 0.3, 0.3));
    Lambertian sphere_blue_mat = Lambertian(Color(0.05, 0.1, 0.4));
    Lambertian sphere_red_mat = Lambertian(Color(0.4, 0.1, 0.1));

    Metal metal_mat = Metal(Color(0.85, 0.85, 0.85), 0.1);
    shared_ptr<Material> metal_ptr = make_shared<Metal>(metal_mat);

    shared_ptr<Material> earth_mat_ptr = make_shared<Lambertian>(earth_mat);
    shared_ptr<Material> sphere_blue_ptr = make_shared<Lambertian>(sphere_blue_mat);
shared_ptr<Material> sphere_red_ptr = make_shared<Lambertian>(sphere_red_mat);
    Sphere earth = Sphere(point3(0, -50.5, -2), 50, earth_mat_ptr);
    Sphere sphere = Sphere(point3(-0.5, 0, -1), 0.5, sphere_blue_ptr);
    Sphere sphere2 = Sphere(point3(1, 0, -1.5), 0.5, metal_ptr);

    world.add(make_shared<Sphere>(earth));
    world.add(make_shared<Sphere>(sphere));
    world.add(make_shared<Sphere>(sphere2));
    
  

    //Render image:
    cam.render(world, output);
}