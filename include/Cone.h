/**
 * @file Cone.h
 * @brief Cone hit detection logic.
 * @author Katarzyna Pi¹tek
 * @date 2026-05-31
 */

#pragma once

#define _USE_MATH_DEFINES
#include <memory>
#include <cmath>
#include "Hittable.h"
#include "Vector_3.h"
#include "Material.h"

 /**
  * @class Cone
  * @brief Finite cone aligned along the Y axis.
  * 
  * @details
  * Implementation of basic hitting logic for a cone in ray tracing.
  * The apex is the tip of the cone. The cone opens downward and is capped at yMin and yMax.
  * 
  * @param apex - world-space position of the cone's tip.
  * @param halfAngle - half-angle of the cone in radians (converted from degrees on construction).
  * @param yMin - lower Y bound of the cone.
  * @param yMax - upper Y bound of the cone.
  * @param mat - specific material for the primitive.
  */
class Cone : public Hittable {
    Vector_3 apex;
    double halfAngle;
    double yMin;
    double yMax;
    std::shared_ptr<Material> mat;

public:
    /**
     * @brief Constructor for Cone.
     *
     * @param apex - value of apex point for the class's attribute.
     * @param halfAngleDeg - half-angle of the cone in degrees.
     * @param yMin - value of lower Y bound for the class's attribute.
     * @param yMax - value of upper Y bound for the class's attribute.
     * @param m - value of specific material for the class's attribute.
     */
    Cone(const Vector_3& apex, double halfAngleDeg, double yMin, double yMax, std::shared_ptr<Material> m);

    /**
     * @brief Tests whether the ray intersects this cone within the given interval.
     *
     * @param r - ray to test against.
     * @param rayT - valid interval of the ray parameter t.
     * @param rec - output record filled with intersection data on a hit.
     * @return true if the ray hits the cone within rayT, false otherwise.
     */
    bool hit(const Ray& r, Interval rayT, HitRecord& rec) const override;
};
