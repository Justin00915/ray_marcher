#pragma once
#include"Vector3.h"
#include"hit_info.h"
#include"material.h"

class SceneObject {
public:
	Vector3 pos;
	Material* mat;

	SceneObject(Vector3 _pos = Vector3(), Material* _mat = nullptr) {
		pos = _pos;
		mat = _mat;
	}

	virtual HitInfo signed_distance(Vector3 pos) { return HitInfo(); };
};

class Sphere : public SceneObject {
public:
	double r;

	Sphere(Vector3 _pos, Material* _mat, double _r){
		pos = _pos;
		mat = _mat;

		r = _r;
	}

	HitInfo signed_distance(Vector3 pos) override;
};

class Box : public SceneObject
{
public:
	Vector3 radii;

	Box(Vector3 _pos, Material* _mat, Vector3 _radii){
		pos = _pos;
		mat = _mat;

		radii = _radii;
	}

	HitInfo signed_distance(Vector3 pos) override;
};

