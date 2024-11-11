#pragma once

#include <ADL/geo.hpp>

#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_video.h>

#include <iostream>
#include <string>
#include <functional>
#include <vector>

namespace ADL {

    struct Config {
        std::string name;
        struct Vec2 size;
        SDL_Window* window;
        std::vector<struct EventHandler> eventHandlers;
    };

    struct Config newConfig(std::string name, struct Vec2 size);

    enum class ExitCode {
        ADL_FATAL_ERR = -1,
        ADL_SUCCESS = 0
    };

    struct EventHandler {
        SDL_EventType eventType;
        std::function<void (bool* running)> handler;
    };

    [[nodiscard]] ExitCode Init_Window(struct Config* config);

    [[nodiscard]] ExitCode AddEventHandler(struct Config* config, EventHandler handler);

    [[nodiscard]] ExitCode Run(const struct Config& config);
}
