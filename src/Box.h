/**
 * @file    Box.h
 * @brief   Axis-aligned bounding box (AABB) hit detection logic.
 * @author  Katarzyna Pi¹tek
 * @date    2026-05-31
 */

#pragma once

#include <algorithm>
#include <memory>
#include "Hittable.h"
#include "Vector_3.h"
#include "Material.h"

 /**
  * @class  Box
  * @brief  Axis-aligned bounding box
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
    * @
    */
    Box(const Vector_3& a, const Vector_3& b, std::shared_ptr<Material> m);

    bool hit(const Ray& r, Interval rayT, HitRecord& rec) const override;
};