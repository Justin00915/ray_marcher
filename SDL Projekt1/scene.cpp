#include"scene.h"

HitInfo Scene::signed_distance(Vector3 pos) {

	if (objects.empty()) {
		return HitInfo{};
	}

	HitInfo hit = objects[0]->signed_distance(pos);
	for (int i = 1; i < objects.size(); i++) {
		HitInfo new_hit = objects[i]->signed_distance(pos);
		if (new_hit.dist < hit.dist) {
			hit = new_hit;
		}
	}

	return hit;
}