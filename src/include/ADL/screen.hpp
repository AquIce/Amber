#pragma once

#include <ADL/geometry.hpp>
#include <ADL/color.hpp>
#include <ADL/config.hpp>

#include <base.hpp>

#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_render.h>

#include <array>
#include <vector>

namespace ADL {

    // General Screen Render

    void ClearScreen(
        ADL::Config* config,
        struct ADL::RGBA rgba = newRGBA()
    );

    NODISCARD bool ChangeRenderRGBA(
        ADL::Config* config,
        struct ADL::RGBA rgba
    );

    void PushRender(
        ADL::Config* config
    );

    // Pixel

    struct Pixel {
        struct ADL::Vec2 geometry;
        struct ADL::RGBA color;
    };

    struct Pixel newPixel(
        struct ADL::Vec2 position,
        struct ADL::RGBA color
    );
    struct Pixel newPixel(
        int x = 0, int y = 0,
        int r = 0, int g = 0, int b = 0, int a = 255
    );

    void RenderPixel(
        ADL::Config* config,
        const struct Pixel* pixel
    );

    // Pixel Line

    struct PixelLine {
        struct ADL::Line2 geometry;
        struct ADL::RGBA color;
    };

    struct PixelLine newPixelLine(
        struct ADL::Line2 line,
        struct ADL::RGBA color = newRGBA()
    );
    struct PixelLine newPixelLine(
        struct ADL::Vec2 start,
        struct ADL::Vec2 end,
        struct ADL::RGBA color = newRGBA()
    );
    struct PixelLine newPixelLine(
        int start_x, int start_y,
        int end_x, int end_y,
        u8 r = 0, u8 g = 0, u8 b = 0, u8 a = 255
    );

    void RenderPixelLine(
        ADL::Config* config,
        const struct PixelLine* line
    );

    // Pixel Rectangle

    struct PixelRect {
        struct ADL::Rect2 geometry;
        struct ADL::RGBA color;
    };

    struct PixelRect newPixelRect(
        struct ADL::Rect2 geometry,
        struct ADL::RGBA color
    );
    struct PixelRect newPixelRect(
        struct ADL::Vec2 origin,
        struct ADL::Vec2 size,
        float angle,
        struct ADL::RGBA color
    );
    struct PixelRect newPixelRect(
        int x = 0, int y = 0,
        int w = 0, int h = 0,
        float angle = 0,
        u8 r = 0, u8 g = 0, u8 b = 0, u8 a = 255
    );

    void RenderPixelRect(
        ADL::Config* config,
        const struct PixelRect* rect
    );
}
