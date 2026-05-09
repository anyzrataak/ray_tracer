#pragma once

#include "Ray.h"
#include "HitRecord.h"
#include "Interval.h"

class Hittable {
public:
    virtual ~Hittable() = default;

    virtual bool hit(const Ray& r, Interval rayT, HitRecord& rec) const = 0;
};