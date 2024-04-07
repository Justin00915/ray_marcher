#pragma once
#include"scene_objects.h"
#include"hit_info.h"
#include"vector3.h"
#include<vector>
#include<memory>
#include"camera.h"

class Scene
{
public:
	std::vector<std::unique_ptr<SceneObject>> objects;
	Camera cam;

	Scene() {}
	void set_camera(Camera cam);
	HitInfo signed_distance(Vector3 pos);
};