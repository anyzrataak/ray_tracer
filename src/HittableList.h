#pragma once

#include <vector>
#include <memory>
#include "Hittable.h"

class HittableList : public Hittable {
    std::vector<std::shared_ptr<Hittable>> objects;

public:
    HittableList() = default;
    explicit HittableList(std::shared_ptr<Hittable> obj) { add(obj); }

    void clear() { objects.clear(); }
    void add(std::shared_ptr<Hittable> obj) { objects.push_back(std::move(obj)); }

    bool hit(const Ray& r, Interval rayT, HitRecord& rec) const;
};
