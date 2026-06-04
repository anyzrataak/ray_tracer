/**
 * @file Cone.h
 * @brief Cone hit detection logic.
 * @author Katarzyna Piatek
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
  */
class Cone : public Hittable {
    Vector_3 apex; ///< World-space position of the cone's tip.
    double halfAngle; ///< Half-angle of the cone in radians.
    double yMin; ///< Lower Y bound of the cone.
    double yMax; ///< Upper Y bound of the cone.
    std::shared_ptr<Material> mat; ///< Specific material for the primitive.

public:
    /**
     * @brief Constructor for Cone.
     *
     * @param apex Value of apex point for the class's attribute.
     * @param halfAngleDeg Half-angle of the cone in degrees.
     * @param yMin Value of lower Y bound for the class's attribute.
     * @param yMax Value of upper Y bound for the class's attribute.
     * @param m Value of specific material for the class's attribute.
     */
    Cone(const Vector_3& apex, double halfAngleDeg, double yMin, double yMax, std::shared_ptr<Material> m);

    /**
     * @brief Tests whether the ray intersects this cone within the given interval.
     *
     * @param r Ray to test against.
     * @param rayT Valid interval of the ray parameter t.
     * @param rec Output record filled with intersection data on a hit.
     * @return True if the ray hits the cone within rayT, false otherwise.
     */
    bool hit(const Ray& r, Interval rayT, HitRecord& rec) const override;
};
