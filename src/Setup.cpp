#include "Setup.h"

void Setup::loadScenes() {
    std::vector<unsigned char> pixels(Width * Height * 3);

    renderScene1(pixels);
    SDL_Texture* tex1 = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB24, SDL_TEXTUREACCESS_STATIC, Width, Height);
    SDL_UpdateTexture(tex1, nullptr, pixels.data(), Width * 3);
    sceneTextures.push_back(tex1);

    std::fill(pixels.begin(), pixels.end(), 0);
    renderScene2(pixels);
    SDL_Texture* tex2 = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB24, SDL_TEXTUREACCESS_STATIC, Width, Height);
    SDL_UpdateTexture(tex2, nullptr, pixels.data(), Width * 3);
    sceneTextures.push_back(tex2);
}

void Setup::handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_EVENT_QUIT) {
            running = false;
        }

        if (event.type == SDL_EVENT_KEY_DOWN) {
            switch (event.key.key) {
            case SDLK_ESCAPE:
                state = States::Menu;
                break;
            case SDLK_1:
                state = States::Scene1;
                break;
            case SDLK_2:
                state = States::Scene2;
                break;
            }
        }

        if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN && event.button.button == SDL_BUTTON_LEFT) {
            float mx = event.button.x;
            float my = event.button.y;

            if (state == States::Menu) {
                if (inMenuButton(mx, my)) {
                    state = States::Scene1;
                }  
                else if (inMenuButton2(mx, my)) {
                    state = States::Scene2;
                }
            }
            else if (state == States::Scene1 || state == States::Scene2) {
                if (inBackButton(mx, my)) {
                    state = States::Menu;
                }
            }
        }
    }
}

void Setup::render() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    switch (state) {
    case States::Menu:
        renderMenu(renderer);
        break;
    case States::Scene1:
        SDL_RenderTexture(renderer, sceneTextures[0], nullptr, nullptr);
        renderBackButton(renderer);
        break;
    case States::Scene2:
        SDL_RenderTexture(renderer, sceneTextures[1], nullptr, nullptr);
        renderBackButton(renderer);
        break;
    }

    SDL_RenderPresent(renderer);
}

Setup::Setup() {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
    }

    if (!SDL_CreateWindowAndRenderer("Ray Tracer", Width, Height, 0, &window, &renderer)) {
        throw std::runtime_error(std::string("SDL_Create Error: ") + SDL_GetError());
    }
    SDL_SetRenderVSync(renderer, 1);
    loadScenes();
    std::clog << "App initialized successfully." << std::endl;
}

Setup::~Setup() {
    for (auto tex : sceneTextures) {
        SDL_DestroyTexture(tex);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Setup::run() {
    while (running) {
        handleEvents();
        render();
    }
}