#pragma once
#include"Vector3.h"
#include"scene_objects.h"
#include"material.h"

struct HitInfo
{
	double dist;
	Vector3 normal;
	Material mat;
};