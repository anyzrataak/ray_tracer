#include "Cone.h"

Cone::Cone(const Vector_3& a, double halfDeg, double yMn, double yMx, std::shared_ptr<Material> m): apex(a), halfAngle(halfDeg* M_PI / 180.0), yMin(yMn), yMax(yMx), mat(std::move(m)) {}

bool Cone::hit(const Ray& r, Interval rayT, HitRecord& rec) const {
    double k = std::tan(halfAngle); k = k * k;
    Vector_3 oc = apex - r.getOrigin();

    double dx = r.getDirection().getX(), dy = r.getDirection().getY(), dz = r.getDirection().getZ();
    double ox = oc.getX(), oy = oc.getY(), oz = oc.getZ();

    double a = dx * dx + dz * dz - k * dy * dy;
    double h = ox * dx + oz * dz - k * oy * dy;
    double c = ox * ox + oz * oz - k * oy * oy;
    double disc = h * h - a * c;

    if (disc < 0.0) {
        return false;
    }

    double sqrtDisc = std::sqrt(disc);
    bool hitSomething = false;
    HitRecord bestRec; 
    double closestT = rayT.getMax();

    for (int sign : {1, -1}) {
        double root = (h + sign * sqrtDisc) / a;

        if (!rayT.surrounds(root) || root >= closestT) {
            continue;
        }

        Vector_3 hp = r.at(root);
        double py = hp.getY();

        if (py < yMin || py > yMax) {
            continue;
        }

        double nx = hp.getX() - apex.getX();
        double nz = hp.getZ() - apex.getZ();
        double ny = -k * (py - apex.getY());
        Vector_3 outward = normalize(Vector_3(nx, ny, nz));
        bestRec.setT(root);
        bestRec.setP(hp);
        bestRec.setFaceNormal(r, outward);
        bestRec.setMat(mat);
        closestT = root;
        hitSomething = true;
    }

    double dy2 = r.getDirection().getY();

    if (std::fabs(dy2) > 1e-8) {
        double t = (yMin - r.getOrigin().getY()) / dy2;

        if (rayT.surrounds(t) && t < closestT) {
            Vector_3 hp = r.at(t);
            double capR = std::fabs((yMin - apex.getY())) * std::tan(halfAngle);
            double ddx = hp.getX() - apex.getX(), ddz = hp.getZ() - apex.getZ();
            
            if (ddx * ddx + ddz * ddz <= capR * capR) {
                bestRec.setT(t);
                bestRec.setP(hp);
                bestRec.setFaceNormal(r, Vector_3(0, -1, 0));
                bestRec.setMat(mat);
                closestT = t; 
                hitSomething = true;
            }
        }
    }
    if (hitSomething) {
        rec = bestRec;
    }

    return hitSomething;
}
