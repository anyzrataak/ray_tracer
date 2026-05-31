/**
 * @file    Constants.h
 * @brief   Global constants shared across all translation units.
 * @author  Katarzyna Pi¹tek
 * @date    2026-05-31
 */

#pragma once

 /**
  * @enum    States
  * @brief   Application state machine (possible program screens).
  */
enum class States { 
	Menu, ///< Main menu screen.
	Scene1, ///< First scene screen.
	Scene2 ///< Second scene screen.
};

constexpr int Width = 1280; ///< Window width in pixels.
constexpr int Height = 720; ///< Window height in pixels.
constexpr int Px = 3; ///< Number of RGB channels per pixel (R, G, B).