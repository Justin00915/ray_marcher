#pragma once
#include<string>
#include<iostream>

class Vector3 {
public:
	double x;
	double y;
	double z;

	Vector3(double _x = 0, double _y = 0, double _z = 0) {
		x = _x;
		y = _y;
		z = _z;
	}

	static Vector3 max(Vector3 v1, Vector3 v2) {
		return Vector3(std::max(v1.x, v2.x), std::max(v1.y, v2.y), std::max(v1.z, v2.z));
	}

	double get_length() {
		return sqrt(x * x + y * y + z * z);
	}
	Vector3 get_normalized() {
		double l = get_length();
		return Vector3(x / l, y / l, z / l);
	}

	Vector3 get_absolute() {
		return Vector3(std::abs(x), std::abs(y), std::abs(z));
	}

	void normalize() {
		double l = get_length();
		x /= l;
		y /= l;
		z /= l;
	}

	void absolutize() {
		x = std::abs(x);
		y = std::abs(y);
		z = std::abs(z);
	}

	double dot(Vector3 other) {
		return x * other.x + y * other.y + z * other.z;
	}

	double get_dist(Vector3 other) {
		return (*this - other).get_length();
	}

	double get_max() {
		return std::fmax(std::max(x, y), z);
	}
	
	double get_abs_max() {
		return std::fmax(std::max(std::abs(x), std::abs(y)), std::abs(z));
	}
	
	double get_min() {
		return std::fmin(std::fmin(x, y), z);
	}
	
	double get_abs_min() {
		return std::fmin(std::fmin(std::abs(x), std::abs(y)), std::abs(z));
	}

	Vector3 operator*(Vector3 other) {
		return Vector3(x * other.x, y * other.y, z * other.z);
	}
	
	Vector3 operator/(Vector3 other) {
		return Vector3(x / other.x, y / other.y, z / other.z);
	}

	Vector3 operator+(Vector3 other) {
		return Vector3(x + other.x, y + other.y, z + other.z);
	}

	Vector3 operator-(Vector3 other) {
		return Vector3(x - other.x, y - other.y, z - other.z);
	}

	Vector3 operator*(double lambda) {
		return Vector3(x * lambda, y * lambda, z * lambda);
	}

	Vector3 operator/(double lambda) {
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

	void march(double lambda) {
		pos = pos + dir * lambda;
	}
};