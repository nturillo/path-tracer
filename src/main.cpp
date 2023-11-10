#include <iostream> 
#include <cfloat>
#include <fstream>

#include "pathtracingutil.hpp"
#include "sphere.hpp"
#include "plane.hpp"
#include "hittable_collection.hpp"
#include "camera.hpp"
#include "material.hpp"
#include "lambertian.hpp"
#include "metal.hpp"

int main() {
    //time
    auto start = std::chrono::high_resolution_clock::now();
    //output
    std::string output_path = "image_output/nice_image.ppm";
    auto output = std::ofstream(output_path);

    //camera
    Camera cam = Camera(Camera::CameraPreset::Standard, point3(0, 0, 1), vec3(0, 0, -1));
    cam.samples_per_pixel = 300;

    //spheres and objects
    Hittable_Collection world;

    Metal earth_mat = Metal(Color(0.3, 0.3, 0.3), 0.06);
    Lambertian sphere_blue_mat = Lambertian(Color(0.05, 0.1, 0.7));
    Lambertian sphere_red_mat = Lambertian(Color(0.7, 0.1, 0.1));
    Metal metal_mat = Metal(Color(0.95, 0.95, 0.95), 0.01);
    shared_ptr<Material> metal_ptr = make_shared<Metal>(metal_mat);
    shared_ptr<Material> earth_mat_ptr = make_shared<Metal>(earth_mat);
    shared_ptr<Material> sphere_blue_ptr = make_shared<Lambertian>(sphere_blue_mat);
    shared_ptr<Material> sphere_red_ptr = make_shared<Lambertian>(sphere_red_mat);
    shared_ptr<Material> yellow_ptr = make_shared<Lambertian>(Lambertian(Color(0.8, 0.8, 0.1)));
    shared_ptr<Material> green_ptr = make_shared<Lambertian>(Lambertian(Color(0.1, 0.8, 0.1)));
    shared_ptr<Material> metal_ptr2 = make_shared<Metal>(Metal(Color(1,1,1), 0.3));
    //Sphere earth = Sphere(point3(0, -50.5, -2), 50, earth_mat_ptr);
    Sphere sphere = Sphere(point3(-0.5, 0, -2), 0.5, sphere_blue_ptr);
    Sphere sphere2 = Sphere(point3(1, 0.2, -2.5), 0.7, metal_ptr);

    Plane earth_plane = Plane(point3(0, -0.5, 0), vec3(0, 1, 0), earth_mat_ptr);

    world.add(make_shared<Plane>(earth_plane));
    world.add(make_shared<Sphere>(sphere));
    world.add(make_shared<Sphere>(sphere2));
    
    //add more spheres
    for (int i = 0; i < 80; i++) {
        double radius = get_random_double(0.05, 0.2);


        double z = get_gaussian_double(-1, 3);
        if (z > -0.3) continue;
        if (z > -1) {
            radius *= 0.6;
        }

        double y = radius - 0.5;

        double x = get_random_double(0.8 * z, -0.8 * z);

        if (z > -1) x = get_random_double(-2, 2);

        //make sure no intersections with big guys
        if (z > -2.25 && z < -1.75) {
            if (x > -0.65 && x < -0.35) continue;
            if (x > 0.65 && x < 1.35) continue;
        }

        int mat_int = i % 6;
        shared_ptr<Material> mat_ptr;
        switch (mat_int) {
        case 0:
            mat_ptr = metal_ptr;
            break;
        case 1:
            mat_ptr = metal_ptr2;
            break;
        case 2:
            mat_ptr = yellow_ptr;
            break;
        case 3:
            mat_ptr = green_ptr;
            break;
        case 4:
            mat_ptr = sphere_red_ptr;
            break;
        case 5:
            mat_ptr = sphere_blue_ptr;
            break;
        default:
            throw std::runtime_error("unexpected case");
        }

        Sphere tempSphere = Sphere(point3(x, y, z), radius, mat_ptr);
        world.add(make_shared<Sphere>(tempSphere));
    }
  

    //Render image:
    cam.render(world, output);

    //time
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(end-start).count();
    std::cout << "Render time: " << duration << " seconds" << std::endl;

}