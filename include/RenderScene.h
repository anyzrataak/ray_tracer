/**
 * @file RenderScene.h
 * @brief Scene rendering entry points and SDL UI helper declarations.
 * @author Katarzyna Pi¹tek
 * @date 2026-05-31
 */

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
#include "Cone.h"
#include "Cylinder.h"

/// @brief Renders scene 1 into a flat RGB pixel buffer.
void renderScene1(std::vector<unsigned char>& pixels);

/// @brief Renders scene 2 into a flat RGB pixel buffer.
void renderScene2(std::vector<unsigned char>& pixels);


/// @brief Draws a single square pixel at (x, y) with the given side length.
static void px(SDL_Renderer* renderer, float x, float y, float size);

/// @brief Draws the scene-1 menu thumbnail pixel at offset (ox, oy).
static void drawPixel1(SDL_Renderer* renderer, float ox, float oy, float size);

/// @brief Draws the scene-2 menu thumbnail pixel at offset (ox, oy).
static void drawPixel2(SDL_Renderer* renderer, float ox, float oy, float size);

/// @brief Draws the back-button icon pixel at offset (ox, oy).
static void drawPixelBack(SDL_Renderer* renderer, float ox, float oy, float size);

/// @brief Draws a filled rectangle button with a border of the given thickness.
static void drawButton(SDL_Renderer* renderer, float bx, float by, float bw, float bh, float border);


/// @brief Renders the main menu screen.
void renderMenu(SDL_Renderer* renderer);

/// @brief Renders the back button overlay.
void renderBackButton(SDL_Renderer* renderer);


/// @brief Returns true if the cursor position (mx, my) is inside the first menu button.
bool inMenuButton(float mx, float my);

/// @brief Returns true if the cursor position (mx, my) is inside the second menu button.
bool inMenuButton2(float mx, float my);

/// @brief Returns true if the cursor position (mx, my) is inside the back button.
bool inBackButton(float mx, float my);