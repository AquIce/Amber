#pragma once

#include <ADL/config.hpp>
#include <ADL/geometry.hpp>
#include <ADL/color.hpp>
#include <ADL/screen.hpp>

#include <base.hpp>

#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_render.h>

#include <iostream>
#include <string>
#include <functional>
#include <vector>

namespace ADL {

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
