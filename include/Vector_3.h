/**
 * @file Vector_3.h
 * @brief 3D vector class and related math utilities.
 * @author Katarzyna Piatek
 * @date 2026-05-31
 */

#pragma once

#include <vector>
#include <cmath>
#include <cfloat>
#include "Constants.h"

 /**
  * @class Vector_3
  * @brief Three-dimensional vector with basic arithmetic operations.
  *
  * @details
  * Stores an (x, y, z) tuple of doubles and provides operators, length queries, and element access used throughout the ray tracer.
  */
class Vector_3 {
	double point[3]; ///< Internal storage: x, y, z components.

public:
	/// @brief Default constructor. Initializes all components to zero.
	Vector_3() :point{ 0, 0, 0 } {}

	/**
	 * @brief Component constructor.
	 * 
	 * @param x X component.
	 * @param y Y component.
	 * @param z Z component.
	 */
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

	/// @brief Negation operator. Returns a vector with all components negated.
	Vector_3 operator-() const {
		return Vector_3(-point[0], -point[1], -point[2]);
	}

	/**
	 * @brief Read-only element access by index.
	 * 
	 * @param i Component index (0=x, 1=y, 2=z).
	 */
	double operator[](int i) const {
		return point[i];
	}

	/**
	 * @brief Writable element access by index.
	 * 
	 * @param i Component index (0=x, 1=y, 2=z).
	 */
	double& operator[](int i) {
		return point[i];
	}

	/**
	 * @brief Component-wise addition assignment.
	 * 
	 * @param vec Vector to add.
	 */
	Vector_3& operator+=(const Vector_3& vec) {
		point[0] += vec.point[0];
		point[1] += vec.point[1];
		point[2] += vec.point[2];
		return *this;
	}

	/**
	 * @brief Scalar multiplication assignment.
	 * 
	 * @param t Scalar to multiply by.
	 */
	Vector_3& operator*=(double t) {
		point[0] *= t;
		point[1] *= t;
		point[2] *= t;
		return *this;
	}

	/**
	 * @brief Scalar division assignment.
	 * 
	 * @param t Scalar to divide by.
	 */
	Vector_3& operator/=(double t) {
		return *this *= 1.0 / t;
	}

	/// @brief Returns the squared length (dot product with itself).
	double length_squared() const {
		return (point[0] * point[0]) + (point[1] * point[1]) + (point[2] * point[2]);
	}

	/// @brief Returns the Euclidean length of the vector.
	double length() const {
		return std::sqrt(length_squared());
	}
};

/**
 * @brief Writes one RGB pixel into the flat pixel buffer.
 * 
 * @param px Pixel buffer to write into.
 * @param x Horizontal pixel coordinate.
 * @param y Vertical pixel coordinate.
 * @param pixel Array of 3 bytes: R, G, B.
 */
inline void add(std::vector<unsigned char>& px, int x, int y, unsigned char pixel[]) {
	int id = (y * Width + x) * 3;
	px[id] = pixel[0];
	px[id + 1] = pixel[1];
	px[id + 2] = pixel[2];
}

/// @brief Component-wise addition of two vectors.
inline Vector_3 operator+(const Vector_3& u, const Vector_3& v) {
	return Vector_3(u.getX() + v.getX(), u.getY() + v.getY(), u.getZ() + v.getZ());
}

/// @brief Component-wise subtraction of two vectors.
inline Vector_3 operator-(const Vector_3& u, const Vector_3& v) {
	return Vector_3(u.getX() - v.getX(), u.getY() - v.getY(), u.getZ() - v.getZ());
}

/// @brief Scalar-vector multiplication.
inline Vector_3 operator*(double scalar, const Vector_3& v) {
	return Vector_3(scalar * v.getX(), scalar * v.getY(), scalar * v.getZ());
}

/// @brief Scalar-vector multiplication.
inline Vector_3 operator*(const Vector_3& v, double scalar) {
	return scalar * v;
}

/// @brief Scalar division.
inline Vector_3 operator/(const Vector_3& v, double scalar) {
	return v * (1.0 / scalar);
}

/// @brief Component-wise multiplication of two vectors.
inline Vector_3 operator*(const Vector_3& u, const Vector_3& v) {
	return Vector_3(u.getX() * v.getX(), u.getY() * v.getY(), u.getZ() * v.getZ());
}

/**
 * @brief Computes the dot product of two vectors.
 * 
 * @param u First vector.
 * @param v Second vector.
 * @return Scalar dot product.
 */
inline double dot(const Vector_3& u, const Vector_3& v) {
	return u.getX() * v.getX() + u.getY() * v.getY() + u.getZ() * v.getZ();
}

/**
 * @brief Computes the cross product of two vectors.
 * 
 * @param u First vector.
 * @param v Second vector.
 * @return Vector perpendicular to both u and v.
 */
inline Vector_3 cross(const Vector_3& u, const Vector_3& v) {
	return Vector_3(u.getY() * v.getZ() - u.getZ() * v.getY(), u.getZ() * v.getX() - u.getX() * v.getZ(), u.getX() * v.getY() - u.getY() * v.getX());
}

/**
 * @brief Returns a unit vector in the direction of v.
 * 
 * @param v Vector to normalize.
 * @return Normalized vector, or zero vector if length is zero.
 */
inline Vector_3 normalize(const Vector_3& v) {
	double l = v.length();
	if (l <= 0) return Vector_3(0, 0, 0);

	return v * (1.0 / l);
}

/**
 * @brief Checks whether a vector is near zero in all components.
 * 
 * @param v Vector to test.
 * @return true if all components are smaller than epsilon.
 */
inline bool nearZero(const Vector_3& v) {
	constexpr double s = DBL_EPSILON;

	return std::fabs(v.getX()) < s && std::fabs(v.getY()) < s && std::fabs(v.getZ()) < s;
}

/**
 * @brief Reflects vector v about normal n.
 * 
 * @param v Incident vector.
 * @param n Surface normal.
 * @return Reflected vector.
 */
inline Vector_3 reflect(const Vector_3& v, const Vector_3& n) {
	return v - 2.0 * dot(v, n) * n;
}

/**
 * @brief Refracts vector uv through a surface with the given index ratio.
 * 
 * @param uv Incident unit vector.
 * @param n Surface normal.
 * @param etai_over_etat Ratio of refractive indices.
 * @return Refracted direction vector.
 */
inline Vector_3 refract(const Vector_3& uv, const Vector_3& n, double etai_over_etat) {
	double cosTheta = std::fmin(dot(-uv, n), 1.0);
	Vector_3 rOutPerp = etai_over_etat * (uv + cosTheta * n);
	Vector_3 rOutParallel = -std::sqrt(std::fabs(1.0 - rOutPerp.length_squared())) * n;

	return rOutPerp + rOutParallel;
}

/// @brief Returns a random double in [0, 1).
inline double randomDouble01() {
	return rand() / (RAND_MAX + 1.0);
}

/**
 * @brief Returns a random double in [lo, hi).
 * 
 * @param lo Lower bound.
 * @param hi Upper bound.
 */
inline double randomDouble(double lo, double hi) {
	return lo + (hi - lo) * randomDouble01();
}

/**
 * @brief Returns a random unit vector uniformly distributed on the unit sphere.
 * 
 * @return Normalized random vector.
 */
inline Vector_3 randomUnitVector() {
	while (true) {
		Vector_3 p(randomDouble(-1, 1), randomDouble(-1, 1), randomDouble(-1, 1));
		double lsq = p.length_squared();
		if (DBL_EPSILON < lsq && lsq <= 1.0) {
			return p / std::sqrt(lsq);
		}
	}
}