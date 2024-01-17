#pragma once
#include<string>
#include<iostream>

class Vector3 {
public:
	float x;
	float y;
	float z;

	Vector3(float _x = 0, float _y = 0, float _z = 0) {
		x = _x;
		y = _y;
		z = _z;
	}

	float get_length() {
		return sqrt(x * x + y * y + z * z);
	}
	Vector3 get_normalized() {
		float l = get_length();
		return Vector3(x / l, y / l, z / l);
	}


	void normalize() {
		float l = get_length();
		x /= l;
		y /= l;
		z /= l;
	}

	float dot(Vector3 other) {
		return x * other.x + y * other.y + z * other.z;
	}

	float get_dist(Vector3 other) {
		return (*this - other).get_length();
	}

	Vector3 operator+(Vector3 other) {
		return Vector3(x + other.x, y + other.y, z + other.z);
	}

	Vector3 operator-(Vector3 other) {
		return Vector3(x - other.x, y - other.y, z - other.z);
	}

	Vector3 operator*(float lambda) {
		return Vector3(x * lambda, y * lambda, z * lambda);
	}

	Vector3 operator/(float lambda) {
		return Vector3(x / lambda, y / lambda, z / lambda);
	}
};

// By uncommentng this you shall cause a bug, because then this function 
// will be defined more then once (if you care fix it, i dont)
//std::ostream& operator<<(std::ostream& os, const Vector3 vec)
//{
//	os << "(" << vec.x << ',' << vec.y << ',' << vec.z << ")";
//	return os;
//}

class Ray {
public:
	Vector3 pos;
	Vector3 dir;

	Ray(Vector3 _pos, Vector3 _dir) {
		pos = _pos;
		dir = _dir;
	}

	void march(float lambda) {
		pos = pos + dir * lambda;
	}
};

struct Sphere
{
	Vector3 pos;
	float r;
};