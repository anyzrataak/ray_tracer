#pragma once
#include <memory>
#include "Hittable.h"

struct CSGInterval {
    double tEnter;
    double tExit;
    HitRecord recEnter;
    HitRecord recExit;
    bool valid = false;
};

CSGInterval getInterval(const Hittable& obj, const Ray& r);

class CSGUnion : public Hittable {
    std::shared_ptr<Hittable> left;
    std::shared_ptr<Hittable> right;

public:
    CSGUnion(std::shared_ptr<Hittable> l, std::shared_ptr<Hittable> r): left(std::move(l)), right(std::move(r)) {}
    bool hit(const Ray& r, Interval rayT, HitRecord& rec) const override;
};

class CSGIntersection : public Hittable {
    std::shared_ptr<Hittable> left;
    std::shared_ptr<Hittable> right;

public:
    CSGIntersection(std::shared_ptr<Hittable> l, std::shared_ptr<Hittable> r): left(std::move(l)), right(std::move(r)) {}
    bool hit(const Ray& r, Interval rayT, HitRecord& rec) const override;
};

class CSGDifference : public Hittable {
    std::shared_ptr<Hittable> left;
    std::shared_ptr<Hittable> right;

public:
    
    CSGDifference(std::shared_ptr<Hittable> l, std::shared_ptr<Hittable> r): left(std::move(l)), right(std::move(r)) {}
    bool hit(const Ray& r, Interval rayT, HitRecord& rec) const override;
};
