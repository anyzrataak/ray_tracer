#include "Box.h"

Box::Box(const Vector_3& a, const Vector_3& b, std::shared_ptr<Material> m) {
    minCorner = Vector_3(std::fmin(a.getX(), b.getX()), std::fmin(a.getY(), b.getY()), std::fmin(a.getZ(), b.getZ()));
    maxCorner = Vector_3(std::fmax(a.getX(), b.getX()), std::fmax(a.getY(), b.getY()), std::fmax(a.getZ(), b.getZ()));
    mat = std::move(m);
}

bool Box::hit(const Ray& r, Interval rayT, HitRecord& rec) const {
    double tMin = rayT.getMin();
    double tMax = rayT.getMax();

    for (int axis = 0; axis < 3; ++axis) {
        double invD = 1.0 / r.getDirection()[axis];
        double t0 = (minCorner[axis] - r.getOrigin()[axis]) * invD;
        double t1 = (maxCorner[axis] - r.getOrigin()[axis]) * invD;

        if (invD < 0.0) {
            std::swap(t0, t1);
        }
            
        tMin = std::fmax(tMin, t0);
        tMax = std::fmin(tMax, t1);

        if (tMax <= tMin) {
            return false;
        }
    }

    rec.setT(tMin);
    rec.setP(r.at(rec.getT()));

    Vector_3 outwardNormal(0, 0, 0);
    for (int axis = 0; axis < 3; ++axis) {
        if (std::fabs(rec.getP()[axis] - minCorner[axis]) < 1e-6) {
            outwardNormal[axis] = -1.0;
        }
        else if (std::fabs(rec.getP()[axis] - maxCorner[axis]) < 1e-6) {
            outwardNormal[axis] = 1.0;
        }
    }

    rec.setFaceNormal(r, outwardNormal);
    rec.setMat(mat);

    return true;
}