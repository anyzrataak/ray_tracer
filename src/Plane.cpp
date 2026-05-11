#include "Plane.h"

bool Plane::hit(const Ray& r, Interval rayT, HitRecord& rec) const {
    double denom = dot(normal, r.getDirection());

    if (std::fabs(denom) < 1e-8)
        return false;

    double t = dot(point - r.getOrigin(), normal) / denom;

    if (!rayT.surrounds(t))
        return false;
    rec.t = t;
    rec.p = r.at(rec.t);
    rec.setFaceNormal(r, normal);
    rec.mat = mat;
    return true;
}