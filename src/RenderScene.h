#pragma once

#include <iostream>
#include <SDL3/SDL.h>
#include "Constants.h"
#include "HittableList.h"
#include "Camera.h"
#include "Material.h"

#include "Sphere.h"
#include "Plane.h"
#include "Box.h"

void renderScene1(std::vector<unsigned char>& pixels);
void renderScene2(std::vector<unsigned char>& pixels);

static void px(SDL_Renderer* renderer, float x, float y, float size);
static void drawPixel1(SDL_Renderer* renderer, float ox, float oy, float size);
static void drawPixel2(SDL_Renderer* renderer, float ox, float oy, float size);
static void drawPixelBack(SDL_Renderer* renderer, float ox, float oy, float size);
static void drawButton(SDL_Renderer* renderer, float bx, float by, float bw, float bh, float border);

void renderMenu(SDL_Renderer* renderer);
void renderBackButton(SDL_Renderer* renderer);

bool inMenuButton(float mx, float my);
bool inMenuButton2(float mx, float my);
bool inBackButton(float mx, float my);