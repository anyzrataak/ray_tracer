/**
 * @file Cylinder.h
 * @brief Cylinder hit detection logic.
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
  * @class Cylinder
  * @brief Finite axis-aligned cylinder.
  * 
  * @details
  * Implementation of basic hitting logic for a cylinder in ray tracing.
  * The cylinder is aligned along the Y axis and capped at yMin and yMax.
  */
class Cylinder : public Hittable {
    Vector_3 center; ///< Base center point of the cylinder.
    double radius; ///< Radius of the cylinder.
    double yMin; ///< Lower Y bound of the cylinder.
    double yMax; ///< Upper Y bound of the cylinder.
    std::shared_ptr<Material> mat; ///< Specific material for the primitive.

public:
    /**
     * @brief Constructor for Cylinder.
     *
     * @param c Value of center point for the class's attribute.
     * @param r Value of radius for the class's attribute.
     * @param yMin Value of lower Y bound for the class's attribute.
     * @param yMax Value of upper Y bound for the class's attribute.
     * @param m Value of specific material for the class's attribute.
     */
    Cylinder(const Vector_3& c, double r, double yMin, double yMax, std::shared_ptr<Material> m);

    /**
     * @brief Tests whether the ray intersects this cylinder within the given interval.
     *
     * @param r Ray to test against.
     * @param rayT Valid interval of the ray parameter t.
     * @param rec Output record filled with intersection data on a hit.
     * @return True if the ray hits the cylinder within rayT, false otherwise.
     */
    bool hit(const Ray& r, Interval rayT, HitRecord& rec) const override;
};
