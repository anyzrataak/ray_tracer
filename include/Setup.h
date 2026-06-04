/**
 * @file Setup.h
 * @brief Application lifecycle management (window, renderer, event loop).
 * @author Katarzyna Pi¹tek
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
  * 
  * @param state - current application state (menu or scene).
  * @param window - SDL window handle.
  * @param renderer - SDL renderer handle.
  * @param sceneTextures - pre-rendered textures for each scene.
  * @param running - flag controlling the main loop.
  */
class Setup {
	States state = States::Menu;
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	std::vector<SDL_Texture*> sceneTextures;
	bool running = true;

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