#pragma once

#include "Vector_3.h"
#include "Ray.h"
#include <memory>

class Material;

class HitRecord {
public:
    Vector_3 p;
    Vector_3 normal;
    double t;
    bool frontFace;
    std::shared_ptr<Material> mat;

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

    void setFaceNormal(const Ray& r, const Vector_3& outwardNormal) {
        frontFace = dot(r.getDirection(), outwardNormal) < 0;
        normal = frontFace ? outwardNormal : -outwardNormal;
    }
};
