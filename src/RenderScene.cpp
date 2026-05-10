#include <vector>
#include "RenderScene.h"

void renderScene1(std::vector<unsigned char>& pixels) {
    std::clog << "Scene #1 - loading..." << std::endl;

    HittableList world;

    auto matSand = std::make_shared<Lambertian>(Vector_3(0.76, 0.70, 0.55));
    world.add(std::make_shared<Plane>(Vector_3(0, -0.5, 0), Vector_3(0, 1, 0), matSand));

    auto matGranite = std::make_shared<Metal>(Vector_3(0.60, 0.58, 0.56), 0.15);
    world.add(std::make_shared<Sphere>(Vector_3(0.0, 0.10, -3.2), 0.60, matGranite));

    auto matCrystal = std::make_shared<Dielectric>(1.5);
    world.add(std::make_shared<Sphere>(Vector_3(-1.0, -0.15, -2.4), 0.35, matCrystal));

    auto matRedRock = std::make_shared<Lambertian>(Vector_3(0.62, 0.32, 0.22));
    world.add(std::make_shared<Sphere>(Vector_3(1.05, -0.28, -2.3), 0.22, matRedRock));

    auto matGrayRock = std::make_shared<Lambertian>(Vector_3(0.48, 0.46, 0.44));
    world.add(std::make_shared<Sphere>(Vector_3(0.55, -0.33, -1.8), 0.17, matGrayRock));

    auto matMoss = std::make_shared<Lambertian>(Vector_3(0.30, 0.42, 0.20));
    world.add(std::make_shared<Sphere>(Vector_3(-1.55, -0.25, -3.0), 0.25, matMoss));

    auto matBrick = std::make_shared<Lambertian>(Vector_3(0.58, 0.28, 0.20));
    world.add(std::make_shared<Box>(Vector_3(-3.0, -0.5, -6.0), Vector_3(-1.1, 0.9, -5.5), matBrick));
    world.add(std::make_shared<Box>(Vector_3(-0.8, -0.5, -6.0), Vector_3(0.8, 0.9, -5.5), matBrick));
    world.add(std::make_shared<Box>(Vector_3(1.1, -0.5, -6.0), Vector_3(3.0, 0.9, -5.5), matBrick));

    Camera cam;
    cam.aspectRatio = (double)Width / Height;
    cam.imageWidth = Width;
    cam.samplesPerPixel = 20;
    cam.maxDepth = 10;
    cam.render(world, pixels);

}

void renderScene2(std::vector<unsigned char>& pixels) {
    std::clog << "Scene #2 - loading..." << std::endl;

    HittableList world;

    auto matFloor = std::make_shared<Lambertian>(Vector_3(0.72, 0.70, 0.68));
    world.add(std::make_shared<Plane>(Vector_3(0, -0.5, 0), Vector_3(0, 1, 0), matFloor));

    auto matPedestal = std::make_shared<Lambertian>(Vector_3(0.55, 0.40, 0.25));
    world.add(std::make_shared<Box>(Vector_3(-1.4, -0.5, -3.2), Vector_3(1.4, 0.1, -2.2), matPedestal));

    auto matCeramic = std::make_shared<Lambertian>(Vector_3(0.15, 0.25, 0.65));
    world.add(std::make_shared<Sphere>(Vector_3(-0.85, 0.45, -2.7), 0.35, matCeramic));

    auto matGlass = std::make_shared<Dielectric>(1.5);
    world.add(std::make_shared<Sphere>(Vector_3(0.0, 0.55, -2.7), 0.45, matGlass));

    auto matGold = std::make_shared<Metal>(Vector_3(0.83, 0.68, 0.22), 0.05);
    world.add(std::make_shared<Sphere>(Vector_3(0.88, 0.42, -2.7), 0.32, matGold));

    auto matCrate = std::make_shared<Lambertian>(Vector_3(0.45, 0.32, 0.18));
    world.add(std::make_shared<Box>(Vector_3(-2.8, -0.5, -5.5), Vector_3(-1.8, 0.6, -4.5), matCrate));
    world.add(std::make_shared<Box>(Vector_3(1.8, -0.5, -5.0), Vector_3(2.7, 0.4, -4.2), matCrate));

    Camera cam;
    cam.aspectRatio = (double)Width / Height;
    cam.imageWidth = Width;
    cam.samplesPerPixel = 20;
    cam.maxDepth = 10;
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
    float bx2 = bx1 + bw + gap;
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