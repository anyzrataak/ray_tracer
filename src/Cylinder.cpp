#include "Cylinder.h"

Cylinder::Cylinder(const Vector_3& c, double r, double yMn, double yMx, std::shared_ptr<Material> m): center(c), radius(std::fmax(0.0, r)), yMin(yMn), yMax(yMx), mat(std::move(m)) {}

bool Cylinder::hit(const Ray& r, Interval rayT, HitRecord& rec) const {
    double ox = center.getX() - r.getOrigin().getX();
    double oz = center.getZ() - r.getOrigin().getZ();
    double dx = r.getDirection().getX();
    double dz = r.getDirection().getZ();

    double a = dx * dx + dz * dz;
    double h = ox * dx + oz * dz;
    double c = ox * ox + oz * oz - radius * radius;
    double disc = h * h - a * c;

    bool hitSomething = false;
    HitRecord bestRec;
    double closestT = rayT.getMax();

    if (disc >= 0.0) {
        double sqrtDisc = std::sqrt(disc);
        for (int sign : {1, -1}) {
            double root = (h + sign * sqrtDisc) / a;
            if (!rayT.surrounds(root) || root >= closestT) continue;
            double y = r.at(root).getY();
            if (y < yMin || y > yMax) continue;
            bestRec.t = root;
            bestRec.p = r.at(root);
            Vector_3 outward = (bestRec.p - Vector_3(center.getX(), bestRec.p.getY(), center.getZ())) / radius;
            bestRec.setFaceNormal(r, outward);
            bestRec.mat = mat;
            closestT = root;
            hitSomething = true;
        }
    }

    double dy = r.getDirection().getY();
    if (std::fabs(dy) > 1e-8) {
        for (double capY : {yMin, yMax}) {
            double t = (capY - r.getOrigin().getY()) / dy;
            if (!rayT.surrounds(t) || t >= closestT) continue;
            Vector_3 hp = r.at(t);
            double dx2 = hp.getX() - center.getX();
            double dz2 = hp.getZ() - center.getZ();
            if (dx2 * dx2 + dz2 * dz2 > radius * radius) continue;
            bestRec.t = t;
            bestRec.p = hp;
            Vector_3 capNormal(0, capY == yMin ? -1.0 : 1.0, 0);
            bestRec.setFaceNormal(r, capNormal);
            bestRec.mat = mat;
            closestT = t;
            hitSomething = true;
        }
    }

    if (hitSomething) rec = bestRec;
    return hitSomething;
}