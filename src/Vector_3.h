#pragma once

#include <vector>
#include <cmath>
#include "Constants.h"


class Vector_3 {
	double point[3];

public:
	Vector_3() :point{ 0, 0, 0 } {}
	Vector_3(double x, double y, double z) :point{ x, y, z } {}

	double getX() const {
		return point[0];
	}

	double getY() const {
		return point[1];
	}

	double getZ() const {
		return point[2];
	}

	Vector_3 operator-() const {
		return Vector_3(-point[0], -point[1], -point[2]);
	}

	double operator[](int i) const {
		return point[i];
	}

	double& operator[](int i) {
		return point[i];
	}

	Vector_3& operator+=(const Vector_3& vec) {
		point[0] += vec.point[0];
		point[1] += vec.point[1];
		point[2] += vec.point[2];
		return *this;
	}

	Vector_3& operator*=(double t) {
		point[0] *= t;
		point[1] *= t;
		point[2] *= t;
		return *this;
	}

	Vector_3& operator/=(double t) {
		return *this *= 1.0 / t;
	}

	double length_squared() const {
		return (point[0] * point[0]) + (point[1] * point[1]) + (point[2] * point[2]);
	}

	double length() const {
		return std::sqrt(length_squared());
	}
};

inline void add(std::vector<unsigned char>& px, int x, int y, unsigned char pixel[]) {
	int id = (y * Width + x) * 3;
	px[id] = pixel[0];
	px[id + 1] = pixel[1];
	px[id + 2] = pixel[2];
}

inline Vector_3 operator+(const Vector_3& u, const Vector_3& v) {
	return Vector_3(u.getX() + v.getX(), u.getY() + v.getY(), u.getZ() + v.getZ());
}

inline Vector_3 operator-(const Vector_3& u, const Vector_3& v) {
	return Vector_3(u.getX() - v.getX(), u.getY() - v.getY(), u.getZ() - v.getZ());
}

inline Vector_3 operator*(double scalar, const Vector_3& v) {
	return Vector_3(scalar * v.getX(), scalar * v.getY(), scalar * v.getZ());
}

inline Vector_3 operator*(const Vector_3& v, double scalar) {
	return scalar * v;
}

inline Vector_3 operator/(const Vector_3& v, double scalar) {
	return v * (1.0 / scalar);
}

inline Vector_3 operator*(const Vector_3& u, const Vector_3& v) {
	return Vector_3(u.getX() * v.getX(), u.getY() * v.getY(), u.getZ() * v.getZ());
}

inline double dot(const Vector_3& u, const Vector_3& v) {
	return u.getX() * v.getX() + u.getY() * v.getY() + u.getZ() * v.getZ();
}

inline Vector_3 cross(const Vector_3& u, const Vector_3& v) {
	return Vector_3(u.getY() * v.getZ() - u.getZ() * v.getY(), u.getZ() * v.getX() - u.getX() * v.getZ(), u.getX() * v.getY() - u.getY() * v.getX());
}

inline Vector_3 normalize(const Vector_3& v) {
	double l = v.length();
	if (l <= 0) return Vector_3(0, 0, 0);
	return v * (1.0 / l);
}