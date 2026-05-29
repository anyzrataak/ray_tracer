#pragma once

#include <memory>
#include "Hittable.h"
#include "Vector_3.h"
#include "Material.h"

class Plane : public Hittable {
    Vector_3 point;
    Vector_3 normal;
    std::shared_ptr<Material> mat;

public:
    Plane(const Vector_3& p, const Vector_3& n, std::shared_ptr<Material> m): point(p), normal(normalize(n)), mat(std::move(m)) {}

    bool hit(const Ray& r, Interval rayT, HitRecord& rec) const override;
};