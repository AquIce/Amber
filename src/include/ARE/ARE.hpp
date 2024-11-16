#pragma once

#include <ARE/log.hpp>
#include <ARE/config.hpp>
#include <ARE/geometry.hpp>
#include <ARE/color.hpp>
#include <ARE/screen.hpp>
#include <ARE/bench.hpp>

#include <base.hpp>

#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_render.h>

#include <string>
#include <functional>
#include <vector>

namespace ARE {

    [[nodiscard]] struct ARE::ReturnCode Init(
        struct Config* config
    );

    [[nodiscard]] struct ARE::ReturnCode AddEventHandler(
        struct Config* config,
        EventHandler handler
    );

    [[nodiscard]] struct ARE::ReturnCode Run(
        struct Config* config
    );
}
