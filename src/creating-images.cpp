#include <iostream> 

#include "color.hpp"
#include "vec3.hpp"
#include "ray.hpp"

color ray_color(const ray& r) {
    vec3 unit_direction = unit_vector(r.get_direction());
    double c = 0.5 * (unit_direction.y() + 1.0);
    double b = 0.5 * (unit_direction.z() + 1.0);
    double a = 0.5 * (unit_direction.x() + 1.0);
    return color (0, 0, c);
}

int main() {
    //image
    const double ASPECT_RATIO = 16.0 / 9.0;
    const int IMAGE_HEIGHT = 300;
    int IMAGE_WIDTH = static_cast<int>(IMAGE_HEIGHT * ASPECT_RATIO);
    if (IMAGE_WIDTH < 1) IMAGE_WIDTH = 1;

    //camera
    const point3 camera_origin = point3(0.0, 0.0, 0.0);
    const double focal_length = 1.0;

    //viewport
    const double viewport_height = 2.0;
    double real_ASPECT_RATIO = static_cast<double>(IMAGE_WIDTH) / IMAGE_HEIGHT;
    double viewport_width = viewport_height * real_ASPECT_RATIO;

    vec3 v_u = vec3(viewport_width, 0.0, 0.0);
    vec3 v_v = vec3(0.0, -viewport_height, 0.0);

    vec3 pixel_delta_u = v_u / IMAGE_WIDTH;
    vec3 pixel_delta_v = v_v / IMAGE_HEIGHT;

    point3 viewport_upper_left = camera_origin + point3(-viewport_width / 2, viewport_height / 2, focal_length);
    point3 upper_left_pixel = viewport_upper_left + pixel_delta_u / 2 + pixel_delta_v / 2;

    //Render image:
    //header
    std::cout << "P3\n" << IMAGE_WIDTH << " " << IMAGE_HEIGHT << "\n255\n";

    //body
    for (int row = 0; row < IMAGE_HEIGHT; row++) {
        //progress bar
        std::clog << "\rScanlines remaining: " << IMAGE_HEIGHT - row << " " << std::flush;
        for (int col = 0; col < IMAGE_WIDTH; col++) {
            point3 pixel_location = upper_left_pixel + pixel_delta_u * col + pixel_delta_v * row;
            point3 ray_origin = camera_origin;
            vec3 ray_direction = pixel_location - camera_origin;
            ray r = ray(ray_origin, ray_direction);

            color c = ray_color(r);

            write_color(std::cout, c);
        }
    }
}