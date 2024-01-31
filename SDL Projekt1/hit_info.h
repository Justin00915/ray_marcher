#pragma once
#include"Vector3.h"
#include"scene_objects.h"

struct HitInfo
{
	double dist;
	Vector3 normal;
	Vector3 col;
	float reflection_index;
};