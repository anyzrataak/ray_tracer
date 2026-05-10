#pragma once

#include <vector>
#include <cmath>
#include "Constants.h"
#include <random>

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

inline bool nearZero(const Vector_3& v) {
	constexpr double s = 1e-8;
	return std::fabs(v.getX()) < s &&
		std::fabs(v.getY()) < s &&
		std::fabs(v.getZ()) < s;
}

inline Vector_3 reflect(const Vector_3& v, const Vector_3& n) {
	return v - 2.0 * dot(v, n) * n;
}

inline Vector_3 refract(const Vector_3& uv, const Vector_3& n, double etai_over_etat) {
	double cosTheta = std::fmin(dot(-uv, n), 1.0);
	Vector_3 rOutPerp = etai_over_etat * (uv + cosTheta * n);
	Vector_3 rOutParallel = -std::sqrt(std::fabs(1.0 - rOutPerp.length_squared())) * n;
	return rOutPerp + rOutParallel;
}

inline double randomDouble01() {
	thread_local std::mt19937 rng{ std::random_device{}() };
	thread_local std::uniform_real_distribution<double> dist(0.0, 1.0);
	return dist(rng);
}

inline double randomDouble(double lo, double hi) {
	return lo + (hi - lo) * randomDouble01();
}

inline Vector_3 randomUnitVector() {
	while (true) {
		Vector_3 p(randomDouble(-1, 1), randomDouble(-1, 1), randomDouble(-1, 1));
		double lsq = p.length_squared();
		if (1e-160 < lsq && lsq <= 1.0) return p / std::sqrt(lsq);
	}
}