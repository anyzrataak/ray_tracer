/**
 * @file    Ray.h
 * @brief   Ray representation used throughout the ray tracer.
 * @author  Katarzyna Piatek
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
  */
class Ray {
    Vector_3 origin; ///< Starting point of the ray.
    Vector_3 dir; ///< Direction vector of the ray.

public:
    Ray() {}

    /**
     * @brief Constructor for Ray.
     *
     * @param orig Value of origin point for the class's attribute.
     * @param direction Value of direction vector for the class's attribute.
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
     * @param t Ray parameter.
     * @return Point origin + t * dir.
     */
    Vector_3 at(double t) const {
        return origin + t * dir;
    }    
};