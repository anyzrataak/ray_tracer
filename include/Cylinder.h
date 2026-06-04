/**
 * @file Cylinder.h
 * @brief Cylinder hit detection logic.
 * @author Katarzyna Pi¹tek
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
  * 
  * @param center - base center point of the cylinder.
  * @param radius - radius of the cylinder.
  * @param yMin - lower Y bound of the cylinder.
  * @param yMax - upper Y bound of the cylinder.
  * @param mat - specific material for the primitive.
  */
class Cylinder : public Hittable {
    Vector_3 center;
    double radius;
    double yMin;
    double yMax;
    std::shared_ptr<Material> mat;

public:
    /**
     * @brief Constructor for Cylinder.
     *
     * @param c - value of center point for the class's attribute.
     * @param r - value of radius for the class's attribute.
     * @param yMin - value of lower Y bound for the class's attribute.
     * @param yMax - value of upper Y bound for the class's attribute.
     * @param m - value of specific material for the class's attribute.
     */
    Cylinder(const Vector_3& c, double r, double yMin, double yMax, std::shared_ptr<Material> m);

    /**
     * @brief Tests whether the ray intersects this cylinder within the given interval.
     *
     * @param r - ray to test against.
     * @param rayT - valid interval of the ray parameter t.
     * @param rec - output record filled with intersection data on a hit.
     * @return true if the ray hits the cylinder within rayT, false otherwise.
     */
    bool hit(const Ray& r, Interval rayT, HitRecord& rec) const override;
};
