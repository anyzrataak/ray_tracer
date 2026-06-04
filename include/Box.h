/**
 * @file Box.h
 * @brief Axis-aligned bounding box (AABB) hit detection logic.
 * @author Katarzyna Pi¹tek
 * @date 2026-05-31
 */

#pragma once

#include <algorithm>
#include <memory>
#include "Hittable.h"
#include "Vector_3.h"
#include "Material.h"

 /**
  * @class Box
  * @brief Axis-aligned bounding box
  *
  * @details
  * Implementation of basic hitting logic for box in ray tracing.
  *
  * @param minCorner - the lower corner.
  * @param maxCorner - the higher corner.
  * @param mat - specific material for primitive.
  */
class Box : public Hittable {
    Vector_3 minCorner;
    Vector_3 maxCorner;
    std::shared_ptr<Material> mat;

public:
    /** 
    * @brief Constructor for AABB.
    * 
    * @param a - value of minimum corner for class's attribute.
    * @param b - value of maximum corner for class's attribute.
    * @param m - value of specific material for class's attribute.
    */
    Box(const Vector_3& a, const Vector_3& b, std::shared_ptr<Material> m);

    /**
     * @brief Tests whether the ray intersects this box within the given interval.
     *
     * @param r - ray to test against.
     * @param rayT - valid interval of the ray parameter t.
     * @param rec - output record filled with intersection data on a hit.
     * @return true if the ray hits the box within rayT, false otherwise.
     */
    bool hit(const Ray& r, Interval rayT, HitRecord& rec) const override;
};