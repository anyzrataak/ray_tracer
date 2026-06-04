#include "Material.h"
#include "Vector_3.h"
#include <cmath>

bool Lambertian::scatter(const Ray& r_in, const HitRecord& rec,
    Vector_3& attenuation, Ray& scattered) const {
    Vector_3 dir = rec.getNormal() + randomUnitVector();

    // Catch degenerate scatter direction when random vector cancels the normal.
    if (nearZero(dir)) {
        dir = rec.getNormal();
    }

    scattered = Ray(rec.getP(), dir);
    attenuation = albedo;

    return true;
}

bool Metal::scatter(const Ray& r_in, const HitRecord& rec,
    Vector_3& attenuation, Ray& scattered) const {
    Vector_3 reflected = reflect(normalize(r_in.getDirection()), rec.getNormal());
    // Fuzz perturbs the reflection to simulate surface roughness.
    reflected = reflected + fuzz * randomUnitVector();
    scattered = Ray(rec.getP(), reflected);
    attenuation = albedo;

    return dot(scattered.getDirection(), rec.getNormal()) > 0;
}

double Dielectric::reflectance(double cosine, double ri) {
    // Schlick's approximation for the probability of reflection at a dielectric interface.
    double r0 = (1.0 - ri) / (1.0 + ri);
    r0 = r0 * r0;

    return r0 + (1.0 - r0) * std::pow(1.0 - cosine, 5);
}

bool Dielectric::scatter(const Ray& r_in, const HitRecord& rec,
    Vector_3& attenuation, Ray& scattered) const {
    attenuation = Vector_3(1.0, 1.0, 1.0);
    // Ratio is inverted when the ray is exiting the material.
    double ri = rec.getFrontFace() ? (1.0 / refractionIndex) : refractionIndex;
    Vector_3 unitDir = normalize(r_in.getDirection());

    double cosTheta = std::fmin(dot(-unitDir, rec.getNormal()), 1.0);
    double sinTheta = std::sqrt(1.0 - cosTheta * cosTheta);

    // Total internal reflection — refraction is physically impossible here.
    bool cannotRefract = ri * sinTheta > 1.0;
    Vector_3 direction;

    if (cannotRefract || reflectance(cosTheta, ri) > randomDouble01()) {
        direction = reflect(unitDir, rec.getNormal());
    }
    else {
        direction = refract(unitDir, rec.getNormal(), ri);
    }

    scattered = Ray(rec.getP(), direction);

    return true;
}
