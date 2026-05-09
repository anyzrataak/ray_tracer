#pragma once

#include <algorithm>
#include "Hittable.h"
#include "Vector_3.h"

class Box : public Hittable {
    Vector_3 minCorner;
    Vector_3 maxCorner;

public:
    Box(const Vector_3& a, const Vector_3& b);

    bool hit(const Ray& r, Interval rayT, HitRecord& rec) const override;
};