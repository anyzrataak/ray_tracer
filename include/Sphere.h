/**
 * @file Sphere.h
 * @brief Sphere hit detection logic.
 * @author Katarzyna Piatek
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
  */
class Sphere : public Hittable {
    Vector_3 center; ///< World-space center of the sphere.
    double radius; ///< Radius of the sphere (>= 0).
    std::shared_ptr<Material> mat; ///< Specific material for the primitive.

public:
    /**
     * @brief Constructor for Sphere.
     *
     * @param c Value of center point for the class's attribute.
     * @param r Value of radius for the class's attribute.
     * @param m Value of specific material for the class's attribute.
     */
    Sphere(const Vector_3& c, double r, std::shared_ptr<Material> m): center(c), radius(std::fmax(0.0, r)), mat(std::move(m)) {}

    /**
     * @brief Tests whether the ray intersects this sphere within the given interval.
     *
     * @param r Ray to test against.
     * @param rayT Valid interval of the ray parameter t.
     * @param rec Output record filled with intersection data on a hit.
     * @return True if the ray hits the sphere within rayT, false otherwise.
     */
    bool hit(const Ray& r, Interval rayT, HitRecord& rec) const override;
};
