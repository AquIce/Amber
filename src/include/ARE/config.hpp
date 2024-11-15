#pragma once

#include <ARE/geometry.hpp>

#include <SDL2/SDL.h>

#include <string>
#include <vector>
#include <functional>

namespace ARE {

    struct ADL_SDL {
        SDL_Window* window;
        SDL_Renderer* renderer;
    };

    struct EventHandler {
        SDL_EventType eventType;
        std::function<void (
            bool* running
        )> handler;
    };

    struct Config {
        std::string name;
        struct Vec2 size;
        struct ADL_SDL sdl;
        std::vector<struct EventHandler> eventHandlers;
    };

    struct Config newConfig(
        std::string name,
        struct Vec2 size
    );
}
