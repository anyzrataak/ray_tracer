#pragma once

#include "Vector_3.h"
#include "Ray.h"
#include <memory>

class Material;

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

    void setFaceNormal(const Ray& r, const Vector_3& outwardNormal) {
        frontFace = dot(r.getDirection(), outwardNormal) < 0;
        normal = frontFace ? outwardNormal : -outwardNormal;
    }
};
