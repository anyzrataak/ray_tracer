/**
 * @file HitRecord.h
 * @brief Data container for ray-object intersection results.
 * @author Katarzyna Pi¹tek
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
 * 
 * @param p - world-space point of intersection.
 * @param normal - surface normal at the hit point.
 * @param t - ray parameter value at the intersection.
 * @param frontFace - true if the ray hit the outer face of the surface.
 * @param mat - material of the intersected object.
 */
class HitRecord {
    Vector_3 p;
    Vector_3 normal;
    double t;
    bool frontFace;
    std::shared_ptr<Material> mat;

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
     * @param r - incident ray.
     * @param outwardNormal - geometry normal pointing away from the surface interior.
     */
    void setFaceNormal(const Ray& r, const Vector_3& outwardNormal) {
        frontFace = dot(r.getDirection(), outwardNormal) < 0;
        normal = frontFace ? outwardNormal : -outwardNormal;
    }
};
