#include "camera.hpp"


Camera::Camera() : aspect_ratio(), image_height(), image_width(), focal_length(), origin(), facing(), viewport_height(), samples_per_pixel(), max_depth() {
	initalize();
}
Camera::Camera(int _image_height, double _aspect_ratio, point3 _origin, vec3 _facing, double _focal_length, double _viewport_height, int _samples_per_pixel, int _max_depth) {
	image_height = _image_height;
	aspect_ratio = _aspect_ratio;
	image_width = static_cast<int>(image_height * aspect_ratio);
	origin = _origin;
	facing = _facing;
	focal_length = _focal_length;
	viewport_height = _viewport_height;
	samples_per_pixel = _samples_per_pixel;
	max_depth = _max_depth;
	initalize();
}
Camera::Camera(CameraPreset preset, point3 _origin, vec3 _facing) {
	switch (preset) {
	case CameraPreset::Standard:
			image_height = 900;
			aspect_ratio = 16.0 / 9.0;
			viewport_height = 0.8;
			samples_per_pixel = 20;
			max_depth = 50;
			break;
	}
	origin = _origin;
	facing = _facing;
	initalize();
}
void Camera::render(const Hittable& world, std::ostream& output) const {
	//header
	output << "P3\n" << image_width << " " << image_height << "\n255\n";

	//ambient color
	Color background(0.35, 0.35, 0.35);

	//body
	for (int row = 0; row < image_height; row++) {
		//progress bar
		std::clog << "\rScanlines remaining: " << image_height - row << " " << std::flush;
		for (int col = 0; col < image_width; col++) {
			
			Color c;
			for (int i = 0; i < samples_per_pixel; i++) {
				ray r = get_ray(row, col);
				c += ray_color(r, world);
			}
			c /= samples_per_pixel;


			write_color(output, c);
		}
	}
}
void Camera::initalize() {
	image_width = static_cast<int>(image_height * aspect_ratio);
	if (image_width < 1) image_width = 1;

	//calculate real aspect ratio
	aspect_ratio = static_cast<double>(image_width) / static_cast<double>(image_height);

	//calculate viewport width
	viewport_width = aspect_ratio * viewport_height;

	//calculate viewport vectors
	v_hor = vec3(viewport_width, 0.0, 0.0);
	v_vert = vec3(0.0, -viewport_height, 0.0);

	pixel_delta_hor = v_hor / image_width;
	pixel_delta_vert = v_vert / image_height;

	//calculate upper left corner of viewport
	facing = unit_vector(facing);
	viewport_upper_left = origin + facing * focal_length - v_hor / 2.0 - v_vert / 2.0;
	viewport_upper_left_pixel = viewport_upper_left + pixel_delta_hor / 2.0 + pixel_delta_vert / 2.0;
}

ray Camera::get_ray(int row, int col) const {
	point3 pixel_location = viewport_upper_left_pixel + pixel_delta_hor * col + pixel_delta_vert * row;
	point3 pixel_sample = pixel_location + pixel_sample_square();
	vec3 ray_direction = (pixel_sample - origin);
	ray r = ray(origin, ray_direction);
	return r;
}

vec3 Camera::pixel_sample_square() const {
	vec3 hor_offset = pixel_delta_hor * (get_random_double() - 0.5);
	vec3 vert_offset = pixel_delta_vert * (get_random_double() - 0.5);
	return hor_offset + vert_offset;
}

Color Camera::ray_color(const ray& r, const Hittable& world) const {
	ray temp_r = r;
	
	vec3 unit_direction = unit_vector(r.get_direction());
	double a = 0.5 * (unit_direction.y() + 1.0);
	Color c = (1.0 - a) * Color(1.0, 1.0, 1.0) + a * Color(0.5, 0.7, 1.0);

	for (int i = 0; i < max_depth; i++) {
		Hit_Record hr;
		if (world.hit(temp_r, Interval(0.001, DBL_MAX), hr)) {
			ray scattered;
			if (!hr.material->scatter(temp_r, hr, c)) break; //ray is absorbed
		}
		else {
			break; //ray doesn't hit anything
		}
	}

	return c;
}
