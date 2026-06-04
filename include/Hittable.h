/**
 * @file Hittable.h
 * @brief Abstract base class for all ray-traceable primitives.
 * @author Katarzyna Pi¹tek
 * @date 2026-05-31
 */

#pragma once

#include "Ray.h"
#include "HitRecord.h"
#include "Interval.h"

 /**
  * @class Hittable
  * @brief Interface for any object that a ray can intersect.
  * 
  * @details
  * Every scene primitive derives from this class and implements the hit() method.
  */
class Hittable {
public:
    virtual ~Hittable() = default;

    /**
     * @brief Tests whether the ray intersects this object within the given interval.
     *
     * @param r - ray to test against.
     * @param rayT - valid interval of the ray parameter t.
     * @param rec - output record filled with intersection data on a hit.
     * @return true if the ray hits the object within rayT, false otherwise.
     */
    virtual bool hit(const Ray& r, Interval rayT, HitRecord& rec) const = 0;
};