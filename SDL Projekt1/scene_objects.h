#pragma once
#include"Vector3.h"
class SceneObject {
public:
	Vector3 pos;
	Vector3 col;

	SceneObject(Vector3 _pos = Vector3(0, 0, 0), Vector3 _col = Vector3(255, 255, 255)) {}

	virtual double SDF(Vector3 pos) { return 0; };
};

class Sphere : public SceneObject {
public:
	float r;

	Sphere(Vector3 _pos, Vector3 _col, float _r) {
		pos = _pos;
		col = _col;

		r = _r;
	}

	double SDF(Vector3 pos) override;
};

class Box : public SceneObject
{
public:
	Vector3 radii;

	Box(Vector3 _pos, Vector3 _col, Vector3 _radii) {
		pos = _pos;
		col = _col;

		radii = _radii;
	}

	double SDF(Vector3 pos) override;
};