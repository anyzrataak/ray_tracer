#include "Camera.h"

void Camera::initialize() {
    imageHeight = std::max(1, (int)(imageWidth / aspectRatio));

    const double focalLength = 1.0;
    const double viewportHeight = 2.0;
    const double viewportWidth = viewportHeight * ((double)imageWidth / imageHeight);
    cameraCenter = Vector_3(0, 0, 0);

    Vector_3 viewportU(viewportWidth, 0, 0);
    Vector_3 viewportV(0, -viewportHeight, 0);
    pixelDeltaU = viewportU / imageWidth;
    pixelDeltaV = viewportV / imageHeight;

    Vector_3 upperLeft = cameraCenter - Vector_3(0, 0, focalLength) - viewportU / 2 - viewportV / 2;
    pixel00Loc = upperLeft + 0.5 * (pixelDeltaU + pixelDeltaV);
}

Vector_3 Camera::randomUnitVector() {
    while (true) {
        Vector_3 p(randomDouble(-1, 1), randomDouble(-1, 1), randomDouble(-1, 1));
        double lsq = p.length_squared();
        if (1e-160 < lsq && lsq <= 1.0)
            return p / std::sqrt(lsq);
    }
}

void Camera::writeColor(std::vector<unsigned char>& px, int x, int y, Vector_3 c) {
    static const Interval intensity(0.000, 0.999);
    unsigned char pxl[3];
    pxl[0] = (unsigned char)(256 * intensity.clamp(linearToGamma(c.getX())));
    pxl[1] = (unsigned char)(256 * intensity.clamp(linearToGamma(c.getY())));
    pxl[2] = (unsigned char)(256 * intensity.clamp(linearToGamma(c.getZ())));
    add(px, x, y, pxl);
}

Vector_3 Camera::rayColor(const Ray& r, int depth, const Hittable& world) {
    if (depth <= 0) return Vector_3(0, 0, 0);

    HitRecord rec;
    if (world.hit(r, Interval(0.001, std::numeric_limits<double>::infinity()), rec)) {
        Ray scattered;
        Vector_3 attenuation;
        if (rec.mat && rec.mat->scatter(r, rec, attenuation, scattered))
            return attenuation * rayColor(scattered, depth - 1, world);
        return Vector_3(0, 0, 0);

    }

    Vector_3 unit = normalize(r.getDirection());
    double a = 0.5 * (unit.getY() + 1.0);
    return (1.0 - a) * Vector_3(1, 1, 1) + a * Vector_3(0.5, 0.7, 1.0);
}

void Camera::render(const Hittable& world, std::vector<unsigned char>& pixels) {
    initialize();
    const double scale = 1.0 / samplesPerPixel;

    for (int j = 0; j < imageHeight; ++j) {
        for (int i = 0; i < imageWidth; ++i) {
            Vector_3 color(0, 0, 0);
            for (int s = 0; s < samplesPerPixel; ++s)
                color += rayColor(getRay(i, j), maxDepth, world);
            writeColor(pixels, i, j, color * scale);
        }
    }
}