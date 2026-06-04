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

    // Try the closer root first; fall back to the farther one if out of range.
    double root = (h - sqrtDisc) / a;
    if (!rayT.surrounds(root)) {
        root = (h + sqrtDisc) / a;
        
        if (!rayT.surrounds(root)) {
            return false;
        }
    }

    rec.setT(root);
    rec.setP(r.at(rec.getT()));
    Vector_3 outwardNormal = (rec.getP() - center) / radius;
    rec.setFaceNormal(r, outwardNormal);
    rec.setMat(mat);

    return true;
}