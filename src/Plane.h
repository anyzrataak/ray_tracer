#pragma once

#include "Hittable.h"
#include "Vector_3.h"

class Plane : public Hittable {
    Vector_3 point;
    Vector_3 normal;

public:
    Plane(const Vector_3& p, const Vector_3& n): point(p), normal(normalize(n)) {}

    bool hit(const Ray& r, Interval rayT, HitRecord& rec) const override;
};