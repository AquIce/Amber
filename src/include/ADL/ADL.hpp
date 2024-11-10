#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>

#include <string>

namespace ADL {
    struct Vec2 {
        int x;
        int y;
    };

    struct ADLConfig {
        std::string name;
        struct Vec2 size;
    };
}
