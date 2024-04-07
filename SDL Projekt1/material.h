#pragma once
#include"vector3.h"

struct Material
{
	Vector3 col;
	double reflection_index;

	Material(Vector3 _col = Vector3(), double _reflection_index = 0) {
		col = _col.get_normalized();
		reflection_index = _reflection_index;
	}
};