#pragma once
#include"scene_objects.h"
#include"hit_info.h"
#include"Vector3.h"
#include<vector>

class Scene
{
public:
	//std::vector<SceneObject> objects;
	SceneObject object;

	Scene() {
		//objects = std::vector<SceneObject>();
		object = Sphere(Vector3(0, 0, 20), Vector3(255, 255, 255), 5);
	}

	HitInfo signed_distance(Vector3 pos);
};