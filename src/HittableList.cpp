#include "HittableList.h"

bool HittableList::hit(const Ray& r, Interval rayT, HitRecord& rec) const {
    HitRecord tempRec;
    bool hitAnything = false;
    double closestSoFar = rayT.getMax();

    for (const auto& obj : objects) {
        if (obj->hit(r, Interval(rayT.getMin(), closestSoFar), tempRec)) {
            hitAnything = true;
            closestSoFar = tempRec.t;
            rec = tempRec;
        }
    }
    return hitAnything;
}