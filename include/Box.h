/**
 * @file Box.h
 * @brief Axis-aligned bounding box (AABB) hit detection logic.
 * @author Katarzyna Piatek
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
  */
class Box : public Hittable {
    Vector_3 minCorner; ///< The lower corner.
    Vector_3 maxCorner; ///< The higher corner.
    std::shared_ptr<Material> mat; ///< Specific material for primitive.

public:
    /** 
    * @brief Constructor for AABB.
    * 
    * @param a Value of minimum corner for class's attribute.
    * @param b Value of maximum corner for class's attribute.
    * @param m Value of specific material for class's attribute.
    */
    Box(const Vector_3& a, const Vector_3& b, std::shared_ptr<Material> m);

    /**
     * @brief Tests whether the ray intersects this box within the given interval.
     *
     * @param r Ray to test against.
     * @param rayT Valid interval of the ray parameter t.
     * @param rec Output record filled with intersection data on a hit.
     * @return True if the ray hits the box within rayT, false otherwise.
     */
    bool hit(const Ray& r, Interval rayT, HitRecord& rec) const override;
};