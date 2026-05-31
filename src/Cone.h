/**
 * @file    Cone.h
 * @brief   Cone hit detection logic.
 * @author  Katarzyna Pi¹tek
 * @date    2026-05-31
 */

#pragma once

#define _USE_MATH_DEFINES
#include <memory>
#include <cmath>
#include "Hittable.h"
#include "Vector_3.h"
#include "Material.h"

class Cone : public Hittable {
    Vector_3 apex;
    double halfAngle;
    double yMin;
    double yMax;
    std::shared_ptr<Material> mat;

public:
    Cone(const Vector_3& apex, double halfAngleDeg, double yMin, double yMax, std::shared_ptr<Material> m);

    bool hit(const Ray& r, Interval rayT, HitRecord& rec) const override;
};
