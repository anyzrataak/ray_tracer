#pragma once
#include "Vector_3.h"

class Ray {
    Vector_3 origin;
    Vector_3 dir;

public:
    Ray() {}
    Ray(const Vector_3& orig, const Vector_3& direction) : origin(orig), dir(direction) {}

    const Vector_3& getOrigin() const { 
        return origin; 
    }

    const Vector_3& getDirection() const { 
        return dir; 
    }

    Vector_3 at(double t) const {
        return origin + t * dir;
    }    
};