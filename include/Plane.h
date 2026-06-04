/**
 * @file Plane.h
 * @brief Infinite plane hit detection logic.
 * @author Katarzyna Pi¹tek
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
  * 
  * @param point - any point lying on the plane.
  * @param normal - unit normal of the plane.
  * @param mat - specific material for the primitive.
  */
class Plane : public Hittable {
    Vector_3 point;
    Vector_3 normal;
    std::shared_ptr<Material> mat;

public:
    /**
     * @brief Constructor for Plane.
     *
     * @param p - value of a point on the plane for the class's attribute.
     * @param n - value of the surface normal for the class's attribute (normalized internally).
     * @param m - value of specific material for the class's attribute.
     */
    Plane(const Vector_3& p, const Vector_3& n, std::shared_ptr<Material> m): point(p), normal(normalize(n)), mat(std::move(m)) {}

    /**
     * @brief Tests whether the ray intersects this plane within the given interval.
     *
     * @param r - ray to test against.
     * @param rayT - valid interval of the ray parameter t.
     * @param rec - output record filled with intersection data on a hit.
     * @return true if the ray hits the plane within rayT, false otherwise.
     */
    bool hit(const Ray& r, Interval rayT, HitRecord& rec) const override;
};