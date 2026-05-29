#pragma once

#include "HitRecord.h"
#include "Ray.h"
#include "Vector_3.h"

class Material {
public:
    virtual ~Material() = default;

    virtual bool scatter(const Ray& r_in, const HitRecord& rec, Vector_3& attenuation, Ray& scattered) const {
        return false;
    }
};

class Lambertian : public Material {
    Vector_3 albedo;

public:
    explicit Lambertian(const Vector_3& albedo) : albedo(albedo) {}

    bool scatter(const Ray& r_in, const HitRecord& rec, Vector_3& attenuation, Ray& scattered) const override;
};

class Metal : public Material {
    Vector_3 albedo;
    double   fuzz;

public:
    Metal(const Vector_3& albedo, double fuzz): albedo(albedo), fuzz(fuzz < 1.0 ? fuzz : 1.0) {}

    bool scatter(const Ray& r_in, const HitRecord& rec, Vector_3& attenuation, Ray& scattered) const override;
};

class Dielectric : public Material {
    double refractionIndex;
    static double reflectance(double cosine, double ri);

public:
    explicit Dielectric(double ri) : refractionIndex(ri) {}

    bool scatter(const Ray& r_in, const HitRecord& rec, Vector_3& attenuation, Ray& scattered) const override;
};