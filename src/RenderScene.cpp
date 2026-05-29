#include <vector>
#include "RenderScene.h"

void renderScene1(std::vector<unsigned char>& pixels) {
    std::clog << "Scene #1 - loading..." << std::endl;

    HittableList world;

    auto matRock = std::make_shared<Lambertian>(Vector_3(0.30, 0.28, 0.26));
    world.add(std::make_shared<Plane>(Vector_3(0, -0.5, 0), Vector_3(0, 1, 0), matRock));

    auto matMirror = std::make_shared<Metal>(Vector_3(0.95, 0.95, 0.95), 0.02);
    world.add(std::make_shared<Sphere>(Vector_3(0.0, 0.30, -3.5), 0.80, matMirror));

    auto matCylCopper = std::make_shared<Metal>(Vector_3(0.72, 0.45, 0.20), 0.12);
    world.add(std::make_shared<Cylinder>(Vector_3(-1.30, -0.5, -2.6), 0.18, -0.5, 0.30, matCylCopper));
    world.add(std::make_shared<Cylinder>(Vector_3(1.30, -0.5, -2.6), 0.18, -0.5, 0.30, matCylCopper));
    world.add(std::make_shared<Cylinder>(Vector_3(-1.30, -0.5, -4.4), 0.18, -0.5, 0.30, matCylCopper));
    world.add(std::make_shared<Cylinder>(Vector_3(1.30, -0.5, -4.4), 0.18, -0.5, 0.30, matCylCopper));

    auto matConeBronze = std::make_shared<Metal>(Vector_3(0.55, 0.35, 0.15), 0.08);
    world.add(std::make_shared<Cone>(Vector_3(-1.30, 0.30, -2.6), 22.0, 0.30, 0.75, matConeBronze));
    world.add(std::make_shared<Cone>(Vector_3(1.30, 0.30, -2.6), 22.0, 0.30, 0.75, matConeBronze));
    world.add(std::make_shared<Cone>(Vector_3(-1.30, 0.30, -4.4), 22.0, 0.30, 0.75, matConeBronze));
    world.add(std::make_shared<Cone>(Vector_3(1.30, 0.30, -4.4), 22.0, 0.30, 0.75, matConeBronze));

    auto matBase = std::make_shared<Lambertian>(Vector_3(0.40, 0.36, 0.32));
    world.add(std::make_shared<Box>(Vector_3(-1.55, -0.50, -2.85), Vector_3(-1.05, -0.30, -2.35), matBase));
    world.add(std::make_shared<Box>(Vector_3(1.05, -0.50, -2.85), Vector_3(1.55, -0.30, -2.35), matBase));
    world.add(std::make_shared<Box>(Vector_3(-1.55, -0.50, -4.65), Vector_3(-1.05, -0.30, -4.15), matBase));
    world.add(std::make_shared<Box>(Vector_3(1.05, -0.50, -4.65), Vector_3(1.55, -0.30, -4.15), matBase));

    auto matGlass = std::make_shared<Dielectric>(1.5);
    world.add(std::make_shared<Sphere>(Vector_3(0.0, -0.32, -1.80), 0.18, matGlass));

    Camera cam;
    cam.aspectRatio = (double)Width / Height;
    cam.imageWidth = Width;
    cam.samplesPerPixel = 20;
    cam.maxDepth = 12;
    cam.render(world, pixels);
}

void renderScene2(std::vector<unsigned char>& pixels) {
    std::clog << "Scene #2 - loading..." << std::endl;

    HittableList world;

    auto matFloor = std::make_shared<Lambertian>(Vector_3(0.72, 0.70, 0.68));
    world.add(std::make_shared<Plane>(Vector_3(0, -0.5, 0), Vector_3(0, 1, 0), matFloor));

    auto matPedestal = std::make_shared<Lambertian>(Vector_3(0.50, 0.38, 0.22));
    world.add(std::make_shared<Box>(Vector_3(-0.55, -0.50, -3.3), Vector_3(0.55, 0.05, -2.3), matPedestal));

    auto matCeramic = std::make_shared<Lambertian>(Vector_3(0.10, 0.20, 0.75));
    world.add(std::make_shared<Sphere>(Vector_3(0.0, 0.60, -2.8), 0.55, matCeramic));

    auto matGlass = std::make_shared<Dielectric>(1.5);
    world.add(std::make_shared<Sphere>(Vector_3(0.90, 0.28, -2.8), 0.23, matGlass));

    auto matMirror = std::make_shared<Metal>(Vector_3(0.90, 0.90, 0.90), 0.02);
    world.add(std::make_shared<Sphere>(Vector_3(-0.90, 0.28, -2.8), 0.23, matMirror));

    auto matBoxDark = std::make_shared<Lambertian>(Vector_3(0.30, 0.22, 0.14));
    world.add(std::make_shared<Box>(Vector_3(-3.0, -0.5, -5.8), Vector_3(-1.8, 0.5, -4.8), matBoxDark));
    world.add(std::make_shared<Box>(Vector_3(-2.8, 0.5, -5.8), Vector_3(-2.0, 1.3, -5.0), matBoxDark));

    auto matBoxLight = std::make_shared<Lambertian>(Vector_3(0.55, 0.42, 0.28));
    world.add(std::make_shared<Box>(Vector_3(1.8, -0.5, -5.8), Vector_3(3.0, 0.5, -4.8), matBoxLight));
    world.add(std::make_shared<Box>(Vector_3(2.0, 0.5, -5.8), Vector_3(2.8, 1.1, -5.0), matBoxLight));

    auto matWall = std::make_shared<Lambertian>(Vector_3(0.60, 0.57, 0.53));
    world.add(std::make_shared<Box>(Vector_3(-3.5, -0.5, -7.0), Vector_3(3.5, 1.5, -6.6), matWall));

    Camera cam;
    cam.aspectRatio = (double)Width / Height;
    cam.imageWidth = Width;
    cam.samplesPerPixel = 20;
    cam.maxDepth = 12;
    cam.render(world, pixels);
}


static void px(SDL_Renderer* renderer, float x, float y, float size) {
    SDL_FRect r = { x, y, size, size };
    SDL_RenderFillRect(renderer, &r);
}

static void drawPixel1(SDL_Renderer* renderer, float ox, float oy, float size) {
    px(renderer, ox, oy, size);
    px(renderer, ox + size, oy, size);
    px(renderer, ox + size, oy + size, size);
    px(renderer, ox + size, oy + size * 2, size);
    px(renderer, ox + size, oy + size * 3, size);
    px(renderer, ox, oy + size * 4, size);
    px(renderer, ox + size, oy + size * 4, size);
    px(renderer, ox + size * 2, oy + size * 4, size);
}

static void drawPixel2(SDL_Renderer* renderer, float ox, float oy, float size) {
    px(renderer, ox, oy, size);
    px(renderer, ox + size, oy, size);
    px(renderer, ox + size * 2, oy, size);
    px(renderer, ox + size * 2, oy + size, size);
    px(renderer, ox, oy + size * 2, size);
    px(renderer, ox + size, oy + size * 2, size);
    px(renderer, ox + size * 2, oy + size * 2, size);
    px(renderer, ox, oy + size * 3, size);
    px(renderer, ox, oy + size * 4, size);
    px(renderer, ox + size, oy + size * 4, size);
    px(renderer, ox + size * 2, oy + size * 4, size);
}

static void drawPixelBack(SDL_Renderer* renderer, float ox, float oy, float size) {
    px(renderer, ox + size * 2, oy, size);
    px(renderer, ox + size, oy + size, size);
    px(renderer, ox, oy + size * 2, size);
    px(renderer, ox + size, oy + size * 3, size);
    px(renderer, ox + size * 2, oy + size * 4, size);

    px(renderer, ox + size, oy + size * 2, size);
    px(renderer, ox + size * 2, oy + size * 2, size);
    px(renderer, ox + size * 3, oy + size * 2, size);
    px(renderer, ox + size * 4, oy + size * 2, size);
    px(renderer, ox + size * 5, oy + size * 2, size);
}

static void drawButton(SDL_Renderer* renderer, float bx, float by, float bw, float bh, float border) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_FRect outer = { bx, by, bw, bh };
    SDL_RenderFillRect(renderer, &outer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_FRect inner = { bx + border, by + border, bw - border * 2, bh - border * 2 };
    SDL_RenderFillRect(renderer, &inner);
}

void renderMenu(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    float bw = 100, bh = 100, border = 4;
    float gap = 20;
    float totalW = bw * 2 + gap;
    float bx1 = (Width - totalW) / 2.0f;
    float bx2 = bx1 + bw + gap;
    float by = (Height - bh) / 2.0f;

    drawButton(renderer, bx1, by, bw, bh, border);
    float pxSize = 10;
    float iconW = 3 * pxSize, iconH = 5 * pxSize;
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    drawPixel1(renderer, bx1 + (bw - iconW) / 2.0f, by + (bh - iconH) / 2.0f, pxSize);

    drawButton(renderer, bx2, by, bw, bh, border);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    drawPixel2(renderer, bx2 + (bw - iconW) / 2.0f, by + (bh - iconH) / 2.0f, pxSize);
}

void renderBackButton(SDL_Renderer* renderer) {
    float bw = 140, bh = 70, border = 4;
    float bx = 10, by = 10;

    drawButton(renderer, bx, by, bw, bh, border);

    float pxSize = 8;
    float iconW = 7 * pxSize;
    float iconH = 5 * pxSize;
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    drawPixelBack(renderer, bx + (bw - iconW) / 2.0f, by + (bh - iconH) / 2.0f, pxSize);
}

bool inMenuButton(float mx, float my) {
    float gap = 20, bw = 100, bh = 100;
    float totalW = bw * 2 + gap;
    float bx1 = (Width - totalW) / 2.0f;
    float by = (Height - bh) / 2.0f;
    return mx >= bx1 && mx <= bx1 + bw && my >= by && my <= by + bh;
}

bool inMenuButton2(float mx, float my) {
    float gap = 20, bw = 100, bh = 100;
    float totalW = bw * 2 + gap;
    float bx2 = (Width - totalW) / 2.0f + bw + gap;
    float by = (Height - bh) / 2.0f;
    return mx >= bx2 && mx <= bx2 + bw && my >= by && my <= by + bh;
}

bool inBackButton(float mx, float my) {
    return mx >= 10 && mx <= 150 && my >= 10 && my <= 80;
}