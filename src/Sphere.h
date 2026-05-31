#pragma once

#include <memory>
#include <cmath>
#include "Hittable.h"
#include "Vector_3.h"
#include "Material.h"

class Sphere : public Hittable {
    Vector_3 center;
    double radius;
    std::shared_ptr<Material> mat;

public:
    Sphere(const Vector_3& c, double r, std::shared_ptr<Material> m): center(c), radius(std::fmax(0.0, r)), mat(std::move(m)) {}

    const Vector_3& getCenter() const { 
        return center; 
    }

    double getRadius() const { 
        return radius; 
    }

    bool hit(const Ray& r, Interval rayT, HitRecord& rec) const override;
};
