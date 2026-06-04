/**
 * @file HitRecord.h
 * @brief Data container for ray-object intersection results.
 * @author Katarzyna Piatek
 * @date 2026-05-31
 */

#pragma once

#include "Vector_3.h"
#include "Ray.h"
#include <memory>

class Material;

/**
 * @class HitRecord
 * @brief Stores all data produced by a successful ray-object intersection.
 * 
 * @details
 * Filled in by each Hittable::hit() implementation and passed to the
 * material's scatter() function to determine the scattered ray and attenuation.
 */
class HitRecord {
    Vector_3 p; ///< World-space point of intersection.
    Vector_3 normal; ///< Surface normal at the hit point.
    double t; ///< Ray parameter value at the intersection.
    bool frontFace; ///< True if the ray hit the outer face of the surface.
    std::shared_ptr<Material> mat; ///< Material of the intersected object.

public:
    const Vector_3& getP() const { 
        return p;
    }

    const Vector_3& getNormal() const {
        return normal; 
    }

    double getT() const { 
        return t; 
    }

    bool getFrontFace() const { 
        return frontFace; 
    }

    std::shared_ptr<Material> getMat() const {
        return mat;
    }

    void setP(const Vector_3& pp) {
        p = pp;
    }

    void setNormal(const Vector_3& n) {
        normal = n;
    }

    void setT(double tt) {
        t = tt;
    }

    void setFrontFace(bool ff) {
        frontFace = ff;
    }

    void setMat(const std::shared_ptr<Material> m) {
        mat = m;
    }

    /**
     * @brief Sets frontFace and normal so the normal always opposes the incident ray.
     *
     * @param r Incident ray.
     * @param outwardNormal Geometry normal pointing away from the surface interior.
     */
    void setFaceNormal(const Ray& r, const Vector_3& outwardNormal) {
        frontFace = dot(r.getDirection(), outwardNormal) < 0;
        normal = frontFace ? outwardNormal : -outwardNormal;
    }
};
