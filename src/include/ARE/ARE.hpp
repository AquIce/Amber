#pragma once

#include <ARE/config.hpp>
#include <ARE/geometry.hpp>
#include <ARE/color.hpp>
#include <ARE/screen.hpp>

#include <base.hpp>

#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_render.h>

#include <iostream>
#include <string>
#include <functional>
#include <vector>

namespace ARE {

    NODISCARD ExitCode Init(
        struct Config* config
    );

    NODISCARD ExitCode AddEventHandler(
        struct Config* config,
        EventHandler handler
    );

    NODISCARD ExitCode Run(
        struct Config* config
    );
}
