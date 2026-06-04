/**
 * @file    Ray.h
 * @brief   Ray representation used throughout the ray tracer.
 * @author  Katarzyna Pi¹tek
 * @date    2026-05-31
 */

#pragma once

#include "Vector_3.h"

 /**
  * @class Ray
  * @brief A parametric ray defined as origin + t * direction.
  * 
  * @details
  * Used to cast primary rays from the camera and secondary rays after material scattering. The point along the ray at parameter t is computed with at().
  * 
  * @param origin - starting point of the ray.
  * @param dir - direction vector of the ray (not required to be normalized).
  */
class Ray {
    Vector_3 origin;
    Vector_3 dir;

public:
    Ray() {}

    /**
     * @brief Constructor for Ray.
     *
     * @param orig - value of origin point for the class's attribute.
     * @param direction - value of direction vector for the class's attribute.
     */
    Ray(const Vector_3& orig, const Vector_3& direction) : origin(orig), dir(direction) {}

    const Vector_3& getOrigin() const { 
        return origin; 
    }

    const Vector_3& getDirection() const { 
        return dir; 
    }

    /**
     * @brief Returns the point along the ray at parameter t.
     *
     * @param t - ray parameter.
     * @return Point origin + t * dir.
     */
    Vector_3 at(double t) const {
        return origin + t * dir;
    }    
};