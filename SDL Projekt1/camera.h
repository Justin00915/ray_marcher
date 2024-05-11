#pragma once
#include"vector3.h"
class Camera
{
public:
	Vector3 pos;

	//0, 0, 0 (default) angles mean, that cam is looking in the z direction
	//angles.x is rotation about x-axis, and so on for the others
	Vector3	angles;
	double spread;

	Camera(Vector3 _pos = Vector3(), Vector3 _angles = Vector3(), double _spread = 0)
		: pos(_pos), angles(_angles), spread(_spread) {}

	void set_angles(Vector3 new_angles) {
		angles = Vector3(
			fmod(new_angles.x, 360),
			fmod(new_angles.y, 360),
			0
		);
	}
};