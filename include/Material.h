/**
 * @file Material.h
 * @brief Material base class and concrete implementations (Lambertian, Metal, Dielectric).
 * @author Katarzyna Piatek
 * @date 2026-05-31
 */

#pragma once

#include "HitRecord.h"
#include "Ray.h"
#include "Vector_3.h"

 /**
  * @class Material
  * @brief Abstract base class for all surface materials.
  * 
  * @details
  * Derived classes implement scatter() to define how an incoming ray interacts with a surface.
  */
class Material {
public:
    virtual ~Material() = default;

    /**
     * @brief Computes the scattered ray and colour attenuation for an intersection.
     *
     * @param r_in Incident ray.
     * @param rec Hit record of the intersection.
     * @param attenuation Output colour multiplier applied to the scattered ray.
     * @param scattered Output scattered ray.
     * @return True if the ray is scattered, false if it is fully absorbed.
     */
    virtual bool scatter(const Ray& r_in, const HitRecord& rec, Vector_3& attenuation, Ray& scattered) const {
        return false;
    }
};

/**
 * @class Lambertian
 * @brief Ideal diffuse material.
 * 
 * @details
 * Scatters rays uniformly in the hemisphere around the surface normal, weighted by the cosine of the angle.
 */
class Lambertian : public Material {
    Vector_3 albedo; ///< Base colour of the surface.

public:
    /**
     * @brief Constructs a Lambertian material.
     * 
     * @param albedo Base colour of the surface.
     */
    explicit Lambertian(const Vector_3& albedo) : albedo(albedo) {}

    bool scatter(const Ray& r_in, const HitRecord& rec, Vector_3& attenuation, Ray& scattered) const override;
};

/**
 * @class Metal
 * @brief Reflective metallic material with optional blur.
 * 
 * @details
 * Reflects rays about the surface normal. The fuzz parameter adds randomness to the reflection direction to simulate brushed metal.
 */
class Metal : public Material {
    Vector_3 albedo; ///< Reflective colour tint of the surface.
    double   fuzz; ///< Blur radius for the reflected ray.

public:
    /**
     * @brief Constructs a Metal material.
     * 
     * @param albedo Reflective colour tint of the surface.
     * @param fuzz Blur radius for the reflected ray (clamped to [0, 1]).
     */
    Metal(const Vector_3& albedo, double fuzz): albedo(albedo), fuzz(fuzz < 1.0 ? fuzz : 1.0) {}

    bool scatter(const Ray& r_in, const HitRecord& rec, Vector_3& attenuation, Ray& scattered) const override;
};

/**
 * @class Dielectric
 * @brief Transparent refractive material (e.g. glass, water).
 *
 * @details
 * Refracts rays according to Snell's law and approximates Fresnel reflectance using Schlick's formula.
 */
class Dielectric : public Material {
    double refractionIndex; ///< Index of refraction of the material.

    /**
     * @brief Approximates Fresnel reflectance using Schlick's formula.
     * 
     * @param cosine Cosine of the angle between the ray and the surface normal.
     * @param ri Ratio of refractive indices.
     * @return Approximate reflectance in [0, 1].
     */
    static double reflectance(double cosine, double ri);

public:
    /**
     * @brief Constructs a Dielectric material.
     * 
     * @param ri Index of refraction.
     */
    explicit Dielectric(double ri) : refractionIndex(ri) {}

    bool scatter(const Ray& r_in, const HitRecord& rec, Vector_3& attenuation, Ray& scattered) const override;
};