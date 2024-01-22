#include"scene.h"

HitInfo Scene::signed_distance(Vector3 pos) {
	HitInfo hit;

	/*if (objects.empty()) {
		return Sphere(Vector3(0, 0, 20), Vector3(255, 255, 255), 5).signed_distance(pos);
	}*/

	//for (auto obj : objects) {
	//	HitInfo new_hit = obj.signed_distance(pos);
	//	if (hit.dist < new_hit.dist) {
	//		hit = new_hit;
	//		//hit = Sphere(Vector3(0, 0, 20), Vector3(255, 255, 255), 5).signed_distance(pos);
	//	}
	//}
	//return hit;
	//return Sphere(Vector3(0, 0, 20), Vector3(255, 255, 255), 5).signed_distance(pos);
	return object.signed_distance(pos);
}