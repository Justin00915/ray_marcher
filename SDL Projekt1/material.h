#pragma once
#include"Vector3.h"

struct Material
{
	Vector3 col;
	float reflection_index;

	Material(Vector3 _col = Vector3(), float _reflection_index = 0) {
		col = _col.get_normalized();
		reflection_index = _reflection_index;
	}
};