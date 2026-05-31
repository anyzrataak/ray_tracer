#include "CSG.h"
#include <limits>
#include <cmath>

CSGInterval getInterval(const Hittable& obj, const Ray& r) {
    CSGInterval res;
    Interval fullRange(1e-4, std::numeric_limits<double>::max());
    HitRecord rec1;

    if (!obj.hit(r, fullRange, rec1)) {
        return res;
    }

    HitRecord rec2;
    Interval afterFirst(rec1.getT() + 1e-4, std::numeric_limits<double>::max());

    if (!obj.hit(r, afterFirst, rec2)) {
        return res;
    }

    res.tEnter = rec1.getT();
    res.tExit = rec2.getT();
    res.recEnter = rec1;
    res.recExit = rec2;
    res.valid = true;

    return res;
}

bool CSGUnion::hit(const Ray& r, Interval rayT, HitRecord& rec) const {
    HitRecord recA, recB;
    bool hitA = left->hit(r, rayT, recA);
    bool hitB = right->hit(r, rayT, recB);

    if (!hitA && !hitB) {
        return false;
    }

    if (hitA && !hitB) { 
        rec = recA; 
        return true; 
    }

    if (!hitA && hitB) { 
        rec = recB; 
        return true; 
    }

    rec = (recA.getT() < recB.getT()) ? recA : recB;

    return true;
}

bool CSGIntersection::hit(const Ray& r, Interval rayT, HitRecord& rec) const {
    CSGInterval ia = getInterval(*left, r);
    CSGInterval ib = getInterval(*right, r);

    if (!ia.valid || !ib.valid) {
        return false;
    }

    double tStart = std::fmax(ia.tEnter, ib.tEnter);
    double tEnd = std::fmin(ia.tExit, ib.tExit);

    if (tStart > tEnd) {
        return false;
    }

    if (!rayT.surrounds(tStart)) {
        return false;
    }

    rec = (ia.tEnter >= ib.tEnter) ? ia.recEnter : ib.recEnter;

    return true;
}

bool CSGDifference::hit(const Ray& r, Interval rayT, HitRecord& rec) const {
    HitRecord recA;
    if (!left->hit(r, rayT, recA)) {
        return false;
    }

    CSGInterval ib = getInterval(*right, r);
    if (!ib.valid || recA.getT() < ib.tEnter || recA.getT() > ib.tExit) {
        rec = recA;
        return true;
    }

    HitRecord recExit;
    if (right->hit(r, Interval(ib.tExit + 1e-4, rayT.getMax()), recExit)) {
        rec = recExit;
        rec.setNormal(-rec.getNormal());
        return true;
    }

    return false;
}