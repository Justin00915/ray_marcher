#pragma once
#include"vector3.h"
class Camera
{
public:
	Vector3 pos;
	Vector3	dir;
	double spread;

	Camera(Vector3 _pos = Vector3(), Vector3 _dir = Vector3(), double _spread = 0)
		: pos(_pos), dir(_dir), spread(_spread) {}
};