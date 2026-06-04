/**
 * @file Setup.h
 * @brief Application lifecycle management.
 * @author Katarzyna Piatek
 * @date 2026-05-31
 */

#pragma once

#include <SDL3/SDL.h>
#include <vector>
#include <exception>
#include <iostream>
#include "Constants.h"
#include "RenderScene.h"

 /**
  * @class Setup
  * @brief Manages SDL initialisation, the main event loop, and scene switching.
  * 
  * @details
  * Creates the window and renderer, pre-renders both scenes into SDL textures, and dispatches input events to navigate between the menu and scenes.
  */
class Setup {
	States state = States::Menu; ///< Current application state.
	SDL_Window* window = nullptr; ///< SDL window handle.
	SDL_Renderer* renderer = nullptr; ///< SDL renderer handle.
	std::vector<SDL_Texture*> sceneTextures; ///< Pre-rendered textures for each scene.
	bool running = true; ///< Flag controlling the main loop.

	/// @brief Pre-renders all scenes and stores them as SDL textures.
	void loadScenes();

	/// @brief Processes pending SDL events and updates the application state.
	void handleEvents();

	/// @brief Draws the current frame based on the active state.
	void render();
public:
	/// @brief Initialises SDL, creates the window and renderer, and loads scenes.
	Setup();

	/// @brief Destroys SDL textures, renderer, and window, then quits SDL.
	~Setup();

	/// @brief Runs the main loop until the user closes the application.
	void run();
};