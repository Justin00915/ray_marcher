#include"scene_objects.h"
#include"hit_info.h"

HitInfo Sphere::signed_distance(Vector3 other_pos) {
	double dist = other_pos.get_dist(pos) - r;
	Vector3 normal = (other_pos - pos).get_normalized();
	return HitInfo{ dist, normal, mat};
}

HitInfo Box::signed_distance(Vector3 other_pos) {
	Vector3 centered_pos = (other_pos - pos);
	double dist = Vector3::max(centered_pos.get_absolutized() - radii, Vector3(0, 0, 0)).get_length();

	int sign = 1;
	Vector3 shenanigans = centered_pos / radii;
	if (shenanigans.get_max() < shenanigans.get_abs_max()) {
		shenanigans = shenanigans * -1;
		sign = -1;
	}
	shenanigans = shenanigans - Vector3(1, 1, 1) * (shenanigans.get_max() - 0.0000001);

	Vector3 normal = Vector3::max(shenanigans, Vector3(0, 0, 0)).get_normalized() * sign;

	return HitInfo{ dist, normal, mat };
}