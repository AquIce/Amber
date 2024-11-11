#pragma once

#include <ADL/geo.hpp>

#include <SDL2/SDL.h>

#include <string>
#include <vector>
#include <functional>

namespace ADL {

    struct ADL_SDL {
        SDL_Window* window;
        SDL_Renderer* renderer;
    };

    enum class ExitCode {
        ADL_FATAL_ERR = -1,
        ADL_SUCCESS = 0
    };

    struct EventHandler {
        SDL_EventType eventType;
        std::function<void (bool* running)> handler;
    };

    struct Config {
        std::string name;
        struct Vec2 size;
        struct ADL_SDL sdl;
        std::vector<struct EventHandler> eventHandlers;
    };

    struct Config newConfig(std::string name, struct Vec2 size);
}
