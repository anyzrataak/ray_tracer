/**
 * @file Camera.h
 * @brief Scene camera configuration.
 * @author Katarzyna Piatek
 * @date 2026-05-31
 */

#pragma once

#include <cmath>
#include <cfloat>
#include "Hittable.h"
#include "HitRecord.h"
#include "Interval.h"
#include "Vector_3.h"
#include "Ray.h"
#include "Constants.h"
#include "Material.h"

 /**
  * @class Camera
  * @brief Perspective camera that generates rays and renders a scene.
  *
  * @details
  * Manages viewport geometry, anti-aliasing, and recursive ray depth. Call render() to produce a pixel buffer.
  */
class Camera {
    Vector_3 cameraCenter; ///< World-space position of the camera.
    Vector_3 pixel00Loc; ///< World-space location of the top-left pixel center.
    Vector_3 pixelDeltaU; ///< Horizontal step between adjacent pixels.
    Vector_3 pixelDeltaV; ///< Vertical step between adjacent pixels.

    int samplesPerPixel = 10; ///< Number of random samples per pixel for anti-aliasing.
    int maxDepth = 50; ///< Maximum ray recursion depth.

    /** @brief Precomputes viewport geometry and pixel grid. */
    void initialize();

    /**
     * @brief Constructs a ray from the camera through pixel (i, j) with a random subpixel offset.
     * 
     * @param i Horizontal pixel index.
     * @param j Vertical pixel index.
     * @return Ray originating from the camera center.
     */
    Ray getRay(int i, int j) const {
        auto offset = const_cast<Camera*>(this)->sampleSquare();
        Vector_3 sample = pixel00Loc + ((i + offset.getX()) * pixelDeltaU) + ((j + offset.getY()) * pixelDeltaV);
        return Ray(cameraCenter, sample - cameraCenter);
    }

    /**
     * @brief Returns a random offset within a unit square centered at the origin.
     * 
     * @return Vector with x and y in [-0.5, 0.5), z = 0.
     */
    Vector_3 sampleSquare() {
        return Vector_3(randomDouble01() - 0.5, randomDouble01() - 0.5, 0);
    }

    /**
     * @brief Applies gamma-2 correction to a linear color component.
     * 
     * @param v Linear color value.
     * @return Gamma-corrected value, or 0 if v is negative.
     */
    static double linearToGamma(double v) {
        return v > 0 ? std::sqrt(v) : 0.0;
    }

    /**
     * @brief Converts a color vector to gamma-corrected bytes and writes it to the pixel buffer.
     * 
     * @param px Pixel buffer to write into.
     * @param x Horizontal pixel coordinate.
     * @param y Vertical pixel coordinate.
     * @param c Linear color value in [0, 1].
     */
    void writeColor(std::vector<unsigned char>& px, int x, int y, Vector_3 c);

    /**
     * @brief Computes the color seen along ray r by recursively tracing the scene.
     * 
     * @param r Ray to trace.
     * @param depth Remaining recursion budget.
     * @param world Scene to test against.
     * @return Color as an RGB vector.
     */
    Vector_3 rayColor(const Ray& r, int depth, const Hittable& world); 

public:
    /**
     * @brief Sets the number of samples per pixel for anti-aliasing.
     * 
     * @param spp Sample count.
     */
    void setSPP(int spp) {
        samplesPerPixel = spp;
    }

    /**
     * @brief Sets the maximum ray recursion depth.
     * 
     * @param md Depth limit.
     */
    void setMD(int md) {
        maxDepth = md;
    }

    /**
     * @brief Renders the scene into a flat RGB pixel buffer.
     * 
     * @param world Scene to render.
     * @param pixels Output buffer of size Width * Height * 3 bytes.
     */
    void render(const Hittable& world, std::vector<unsigned char>& pixels);
};
