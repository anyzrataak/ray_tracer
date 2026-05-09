#pragma once

#include <SDL3/SDL.h>
#include <vector>
#include <exception>
#include <iostream>
#include "Constants.h"
#include "RenderScene.h"

class Setup {
	States state = States::Menu;
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	std::vector<SDL_Texture*> sceneTextures;
	bool running = true;

	void loadScenes();
	void handleEvents();
	void render();
public:
	Setup();
	~Setup();

	void run();
};