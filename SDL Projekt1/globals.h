#pragma once
const int WINDOW_WIDTH = 1000;
const int WINDOW_HEIGHT = 600;
const int max_n_threads = 15;
const double spread = 0.001;
const int max_marching_iters = 500;
const int max_reflections = 10;
const double min_marching_dist = 0.00001;
const double max_cam_dist = 100;
const double RADIANS_TO_DEGREE = M_PI / 180;

const Vector3 HIT_AN_OBJECT_COLOR = Vector3(-1, -1, -1);
extern Vector3 sun_light_dir;

struct Pixel
{
	int x = 0;
	int y = 0;
	Vector3 col;
};

inline Vector3 pixel_to_world_coords(double x, double y) {
	x = (2 * x - WINDOW_WIDTH);
	y = -(2 * y - WINDOW_HEIGHT);
	return(Vector3(x, y, 0));
}

//angle in degrees
inline Vector3 rotate_by_angle(Vector3 vector, double angle) {
	return Vector3(
		vector.x * cos(angle) - vector.z * sin(angle),
		vector.y,
		vector.x * sin(angle) + vector.z * cos(angle)
	);
}