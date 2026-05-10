#pragma once

#include <algorithm>
#include <memory>
#include "Hittable.h"
#include "Vector_3.h"
#include "Material.h"

class Box : public Hittable {
    Vector_3 minCorner;
    Vector_3 maxCorner;
    std::shared_ptr<Material> mat;

public:
    Box(const Vector_3& a, const Vector_3& b, std::shared_ptr<Material> m);

    bool hit(const Ray& r, Interval rayT, HitRecord& rec) const override;
};