#pragma once

#include <cmath>
#include "Hittable.h"
#include "Vector_3.h"

class Sphere : public Hittable {
    Vector_3 center;
    double radius;

public:
    Sphere(const Vector_3& c, double r): center(c), radius(std::fmax(0.0, r)) {}

    const Vector_3& getCenter() const { return center; }
    double getRadius() const { return radius; }

    bool hit(const Ray& r, Interval rayT, HitRecord& rec) const override;
};
