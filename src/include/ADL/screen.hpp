#pragma once

#include <ADL/geometry.hpp>
#include <ADL/color.hpp>
#include <ADL/config.hpp>

#include <base.hpp>

#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_render.h>

namespace ADL {

    void ClearScreen(
        ADL::Config* config,
        struct RGBA rgba = newRGBA()
    );

    NODISCARD bool ChangeRenderRGBA(
        ADL::Config* config,
        struct RGBA rgba
    );

    void Flush(
        ADL::Config* config
    );

    struct Pixel {
        struct Vec2 geometry;
        struct RGBA color;
    };

    struct Pixel newPixel(
        struct Vec2 position,
        struct RGBA color
    );
    struct Pixel newPixel(
        int x = 0, int y = 0,
        int r = 0, int g = 0, int b = 0, int a = 255
    );

    void RenderPixel(
        ADL::Config* config,
        const struct Pixel* pixel
    );

    struct PixelLine {
        struct Line2 geometry;
        struct RGBA color;
    };

    struct PixelLine newPixelLine(
        struct Line2 line,
        struct RGBA color = newRGBA()
    );
    struct PixelLine newPixelLine(
        struct Vec2 start,
        struct Vec2 end,
        struct RGBA color = newRGBA()
    );
    struct PixelLine newPixelLine(
        int start_x, int start_y,
        int end_x, int end_y,
        u8 r = 0, u8 g = 0, u8 b = 0, u8 a = 255
    );

    void RenderLine(
        ADL::Config* config,
        const struct PixelLine* line
    );
}
