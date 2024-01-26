#pragma once
#include"scene_objects.h"
#include"hit_info.h"
#include"Vector3.h"
#include<vector>
#include<memory>

class Scene
{
public:
	std::vector<std::unique_ptr<SceneObject>> objects;

	Scene() {}

	HitInfo signed_distance(Vector3 pos);
};