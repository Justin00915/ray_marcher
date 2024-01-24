#include"scene.h"

HitInfo Scene::signed_distance(Vector3 pos) {

	if (objects.empty()) {
		return Sphere(Vector3(0, 0, 20), Vector3(255, 255, 255), 5).signed_distance(pos);
	}

	//for (auto obj : objects) {
	//	HitInfo new_hit = obj.signed_distance(pos);
	//	if (hit.dist < new_hit.dist) {
	//		hit = new_hit;
	//		//hit = Sphere(Vector3(0, 0, 20), Vector3(255, 255, 255), 5).signed_distance(pos);
	//	}
	//}

	HitInfo hit = objects[0]->signed_distance(pos);
	for (int i = 1; i < objects.size(); i++) {
		HitInfo new_hit = objects[i]->signed_distance(pos);
		if (new_hit.dist < hit.dist) {
			hit = new_hit;
		}
	}

	return hit;
	//return Sphere(Vector3(0, 0, 20), Vector3(255, 255, 255), 5).signed_distance(pos);
	//return object.signed_distance(pos);
}