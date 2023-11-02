#pragma once

#include <iostream>

#include "pathtracingutil.hpp"
#include "hittable.hpp"


class Camera
{
public:
	enum CameraPreset {
		Standard
	};
	Camera();
	Camera(int _image_height, double _aspect_ratio, point3 origin, vec3 facing, double focal_length, double viewport_height);
	Camera(CameraPreset preset, point3 _origin, vec3 _facing);
	void render(const Hittable& world, std::ostream& output) const;
	void initalize();

	//camera
	double aspect_ratio;
	int image_height;
	vec3 origin;
	vec3 facing;
	double focal_length;


	//viewport
	double viewport_height;

private:
	//camera
	int image_width;

	//viewport
	double viewport_width;
	double real_aspect_ratio;

	vec3 v_hor;
	vec3 v_vert;

	vec3 pixel_delta_hor;
	vec3 pixel_delta_vert;

	point3 viewport_upper_left;
	point3 viewport_upper_left_pixel;

	Color ray_color(const ray& r, const Hittable::Hit_Record& hr) const;
};