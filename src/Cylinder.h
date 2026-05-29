#pragma once

#include <memory>
#include <cmath>
#include "Hittable.h"
#include "Vector_3.h"
#include "Material.h"

class Cylinder : public Hittable {
    Vector_3 center;
    double radius;
    double yMin;
    double yMax;
    std::shared_ptr<Material> mat;

public:
    Cylinder(const Vector_3& c, double r, double yMin, double yMax, std::shared_ptr<Material> m);
    bool hit(const Ray& r, Interval rayT, HitRecord& rec) const override;
};
