/**
 * @file Plane.h
 * @brief Infinite plane hit detection logic.
 * @author Katarzyna Piatek
 * @date 2026-05-31
 */
#pragma once

#include <memory>
#include "Hittable.h"
#include "Vector_3.h"
#include "Material.h"

 /**
  * @class Plane
  * @brief Infinite flat plane defined by a point and a normal.
  * 
  * @details
  * Implementation of basic hitting logic for an infinite plane in ray tracing.
  * The normal is automatically normalized on construction.
  */
class Plane : public Hittable {
    Vector_3 point; ///< Any point lying on the plane.
    Vector_3 normal; ///< Unit normal of the plane.
    std::shared_ptr<Material> mat; ///< Specific material for the primitive.

public:
    /**
     * @brief Constructor for Plane.
     *
     * @param p Value of a point on the plane for the class's attribute.
     * @param n Value of the surface normal for the class's attribute (normalized internally).
     * @param m Value of specific material for the class's attribute.
     */
    Plane(const Vector_3& p, const Vector_3& n, std::shared_ptr<Material> m): point(p), normal(normalize(n)), mat(std::move(m)) {}

    /**
     * @brief Tests whether the ray intersects this plane within the given interval.
     *
     * @param r Ray to test against.
     * @param rayT Valid interval of the ray parameter t.
     * @param rec Output record filled with intersection data on a hit.
     * @return True if the ray hits the plane within rayT, false otherwise.
     */
    bool hit(const Ray& r, Interval rayT, HitRecord& rec) const override;
};