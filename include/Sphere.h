/**
 * @file Sphere.h
 * @brief Sphere hit detection logic.
 * @author Katarzyna Pi
 * @date 2026-05-31
 */

#pragma once

#include <memory>
#include <cmath>
#include "Hittable.h"
#include "Vector_3.h"
#include "Material.h"

 /**
  * @class Sphere
  * @brief A geometric sphere primitive.
  * 
  * @details
  * Implementation of basic hitting logic for a sphere in ray tracing.
  * The radius is clamped to a minimum of 0 on construction.
  * 
  * @param center - world-space center of the sphere.
  * @param radius - radius of the sphere (>= 0).
  * @param mat - specific material for the primitive.
  */
class Sphere : public Hittable {
    Vector_3 center;
    double radius;
    std::shared_ptr<Material> mat;

public:
    /**
     * @brief Constructor for Sphere.
     *
     * @param c - value of center point for the class's attribute.
     * @param r - value of radius for the class's attribute.
     * @param m - value of specific material for the class's attribute.
     */
    Sphere(const Vector_3& c, double r, std::shared_ptr<Material> m): center(c), radius(std::fmax(0.0, r)), mat(std::move(m)) {}

    /**
     * @brief Tests whether the ray intersects this sphere within the given interval.
     *
     * @param r - ray to test against.
     * @param rayT - valid interval of the ray parameter t.
     * @param rec - output record filled with intersection data on a hit.
     * @return true if the ray hits the sphere within rayT, false otherwise.
     */
    bool hit(const Ray& r, Interval rayT, HitRecord& rec) const override;
};
