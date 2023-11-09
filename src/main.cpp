#include <iostream> 
#include <cfloat>
#include <fstream>

#include "pathtracingutil.hpp"
#include "sphere.hpp"
#include "hittable_collection.hpp"
#include "camera.hpp"
#include "material.hpp"
#include "lambertian.hpp"



bool hit_sphere(const point3& center, double radius, const ray& r) {
    vec3 oc = center - r.get_origin();
    double a = r.get_direction().length_squared();
    double b = 2.0 * dot(oc, r.get_direction());
    double c = oc.length_squared() - radius * radius;
    double discriminant = b * b - 4 * a * c;
    return (discriminant > 0);
}


int main() {
    //test random vectors
    vec3 avg;
    int samples = 0;
    for (int i = 0; i < 1000; i++) {
        vec3 random_vec = vec3::random_unit_vec();
        if (random_vec.z() < 0) continue;
        avg += random_vec;
        samples++;
    }
    avg /= samples;
    std::cout << "Average random vector: " << avg << std::endl;
    //output
    std::string output_path = "image_output/test_image.ppm";
    auto output = std::ofstream(output_path);

    //camera
    Camera cam = Camera(Camera::CameraPreset::Standard, point3(0, 0, 0), vec3(0, 0, -1));
    cam.samples_per_pixel = 20;

    //spheres and objects
    Hittable_Collection world;
    Lambertian sphere_mat = Lambertian(Color(0.5, 0.5, 0.5));
    shared_ptr<Material> sphere_mat_ptr = make_shared<Lambertian>(sphere_mat);
    Sphere earth = Sphere(point3(0, -50.5, -2), 50, sphere_mat_ptr);
    Sphere sphere = Sphere(point3(0, 0, -1), 0.5, sphere_mat_ptr);

    world.add(make_shared<Sphere>(earth));
    world.add(make_shared<Sphere>(sphere));
    
  

    //Render image:
    cam.render(world, output);
}