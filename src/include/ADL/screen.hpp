#pragma once

#include <ADL/geo.hpp>

#include <base.hpp>

#include <SDL2/SDL_stdinc.h>

namespace ADL {
    struct RGBA {
        u8 r;
        u8 g;
        u8 b;
        u8 a;
    };

    struct RGBA newRGBA(u8 r = 0, u8 g = 0, u8 b = 0, u8 a = 255);

    struct Pixel {
        struct Vec2 position;
        struct RGBA color;
    };

    struct Pixel newPixel(int x = 0, int y = 0, int r = 0, int g = 0, int b = 0, int a = 255);
    struct Pixel newPixel(struct Vec2 position, struct RGBA color);
}
