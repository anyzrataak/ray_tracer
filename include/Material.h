/**
 * @file Material.h
 * @brief Material base class and concrete implementations (Lambertian, Metal, Dielectric).
 * @author Katarzyna Pi¹tek
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
     * @param r_in - incident ray.
     * @param rec - hit record of the intersection.
     * @param attenuation - output colour multiplier applied to the scattered ray.
     * @param scattered - output scattered ray.
     * @return true if the ray is scattered, false if it is fully absorbed.
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
 * 
 * @param albedo - base colour of the surface.
 */
class Lambertian : public Material {
    Vector_3 albedo;

public:
    explicit Lambertian(const Vector_3& albedo) : albedo(albedo) {}

    bool scatter(const Ray& r_in, const HitRecord& rec, Vector_3& attenuation, Ray& scattered) const override;
};

/**
 * @class Metal
 * @brief Reflective metallic material with optional blur.
 * 
 * @details
 * Reflects rays about the surface normal. The fuzz parameter adds randomness to the reflection direction to simulate brushed metal.
 * 
 * @param albedo - reflective colour tint of the surface.
 * @param fuzz - blur radius for the reflected ray (clamped to [0, 1]).
 */
class Metal : public Material {
    Vector_3 albedo;
    double   fuzz;

public:
    Metal(const Vector_3& albedo, double fuzz): albedo(albedo), fuzz(fuzz < 1.0 ? fuzz : 1.0) {}

    bool scatter(const Ray& r_in, const HitRecord& rec, Vector_3& attenuation, Ray& scattered) const override;
};

/**
 * @class Dielectric
 * @brief Transparent refractive material (e.g. glass, water).
 * 
 * @details
 * Refracts rays according to Snell's law and approximates Fresnel reflectance using Schlick's formula.
 * 
 * @param refractionIndex - index of refraction of the material.
 */
class Dielectric : public Material {
    double refractionIndex;
    static double reflectance(double cosine, double ri);

public:
    explicit Dielectric(double ri) : refractionIndex(ri) {}

    bool scatter(const Ray& r_in, const HitRecord& rec, Vector_3& attenuation, Ray& scattered) const override;
};