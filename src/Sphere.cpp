#include "Sphere.h"

bool Sphere::hit(const Ray& r, Interval rayT, HitRecord& rec) const {
    Vector_3 oc = center - r.getOrigin();

    double a = r.getDirection().length_squared();
    double h = dot(r.getDirection(), oc);
    double c = oc.length_squared() - radius * radius;
    double disc = h * h - a * c;

    if (disc < 0) {
        return false;
    }

    double sqrtDisc = std::sqrt(disc);

    double root = (h - sqrtDisc) / a;
    if (!rayT.surrounds(root)) {
        root = (h + sqrtDisc) / a;
        if (!rayT.surrounds(root)) return false;
    }

    rec.t = root;
    rec.p = r.at(rec.t);
    Vector_3 outwardNormal = (rec.p - center) / radius;
    rec.setFaceNormal(r, outwardNormal);
    return true;
}