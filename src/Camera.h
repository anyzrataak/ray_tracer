#pragma once

#include <random>
#include <cmath>
#include "Hittable.h"
#include "HitRecord.h"
#include "Interval.h"
#include "Vector_3.h"
#include "Ray.h"
#include "Constants.h"
#include "Material.h"

class Camera {
    int imageHeight;
    Vector_3 cameraCenter;
    Vector_3 pixel00Loc;
    Vector_3 pixelDeltaU;
    Vector_3 pixelDeltaV;
    std::mt19937 rng{ std::random_device{}() };
    std::uniform_real_distribution<double> dist{ 0.0, 1.0 };

    double randomDouble() { 
        return dist(rng); 
    }

    double randomDouble(double lo, double hi) { 
        return lo + (hi - lo) * randomDouble(); 
    }

    void initialize();

    Ray getRay(int i, int j) const {
        auto offset = const_cast<Camera*>(this)->sampleSquare();
        Vector_3 sample = pixel00Loc + ((i + offset.getX()) * pixelDeltaU) + ((j + offset.getY()) * pixelDeltaV);
        return Ray(cameraCenter, sample - cameraCenter);
    }

    Vector_3 sampleSquare() {
        return Vector_3(randomDouble() - 0.5, randomDouble() - 0.5, 0);
    }

    Vector_3 randomUnitVector();

    static double linearToGamma(double v) {
        return v > 0 ? std::sqrt(v) : 0.0;
    }

    void writeColor(std::vector<unsigned char>& px, int x, int y, Vector_3 c);

    Vector_3 rayColor(const Ray& r, int depth, const Hittable& world); 

public:
    double aspectRatio = 16.0 / 9.0;
    int imageWidth = Width;
    int samplesPerPixel = 10;
    int maxDepth = 50;

    void render(const Hittable& world, std::vector<unsigned char>& pixels);
};
