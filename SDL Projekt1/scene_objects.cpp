#include"scene_objects.h"

double Sphere::SDF(Vector3 other_pos) {
	return other_pos.get_dist(pos) - r;
}

double Box::SDF(Vector3 pos) {
	double dists = Vector3::max((pos - this->pos).get_absolute() - radii, Vector3(0, 0, 0)).get_length();
	return dists;
}