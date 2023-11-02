#include "camera.hpp"


Camera::Camera() : aspect_ratio(), image_height(), image_width(), focal_length(), origin(), facing(), viewport_height() {
	initalize();
}
Camera::Camera(int _image_height, double _aspect_ratio, point3 _origin, vec3 _facing, double _focal_length, double _viewport_height) {
	image_height = _image_height;
	aspect_ratio = _aspect_ratio;
	image_width = static_cast<int>(image_height * aspect_ratio);
	origin = _origin;
	facing = _facing;
	focal_length = _focal_length;
	viewport_height = _viewport_height;
	initalize();
}
Camera::Camera(CameraPreset preset, point3 _origin, vec3 _facing) {
	switch (preset) {
	case CameraPreset::Standard:
			image_height = 300;
			aspect_ratio = 16.0 / 9.0;
			focal_length = 1.0;
			viewport_height = 2.0;
			break;
	}
	origin = _origin;
	facing = _facing;
	initalize();
}
void Camera::render(const Hittable& world, std::ostream& output) const {
	//header
	output << "P3\n" << image_width << " " << image_height << "\n255\n";

	//body
	for (int row = 0; row < image_height; row++) {
		//progress bar
		std::clog << "\rScanlines remaining: " << image_height - row << " " << std::flush;
		for (int col = 0; col < image_width; col++) {
			//calculate ray
			point3 pixel_location = viewport_upper_left_pixel + pixel_delta_hor * col + pixel_delta_vert * row;
			point3 ray_origin = origin;
			vec3 ray_direction = (pixel_location - origin);
			ray r = ray(ray_origin, ray_direction);


			//ray hits
			Hittable::Hit_Record hr;

			Color c = world.hit(r, Interval::positive, hr) ? ray_color(r, hr) : Color(0.4, 0.4, 0.4);

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

Color Camera::ray_color(const ray& r, const Hittable::Hit_Record& hr) const {
	//normal
	vec3 normal = hr.normal;
	normal = unit_vector(normal);

	//color
	Color c = 0.5 * (normal + Color(1.0, 1.0, 1.0));

	return c;
}
