#pragma once

#include <ARE/geometry.hpp>
#include <ARE/color.hpp>
#include <ARE/config.hpp>

#include <base.hpp>

#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_render.h>

#include <array>
#include <vector>

namespace ARE {

    // General Screen Render

    void ClearScreen(
        ARE::Config* config,
        struct ARE::RGBA rgba = newRGBA()
    );

    NODISCARD bool ChangeRenderRGBA(
        ARE::Config* config,
        struct ARE::RGBA rgba
    );

    void PushRender(
        ARE::Config* config
    );

    // Pixel

    struct Pixel {
        struct ARE::Vec2 geometry;
        struct ARE::RGBA color;
    };

    struct Pixel newPixel(
        struct ARE::Vec2 position,
        struct ARE::RGBA color
    );
    struct Pixel newPixel(
        int x = 0, int y = 0,
        int r = 0, int g = 0, int b = 0, int a = 255
    );

    void RenderPixel(
        ARE::Config* config,
        const struct Pixel* pixel
    );

    // Pixel Line

    struct PixelLine {
        struct ARE::Line2 geometry;
        struct ARE::RGBA color;
    };

    struct PixelLine newPixelLine(
        struct ARE::Line2 line,
        struct ARE::RGBA color = newRGBA()
    );
    struct PixelLine newPixelLine(
        struct ARE::Vec2 start,
        struct ARE::Vec2 end,
        struct ARE::RGBA color = newRGBA()
    );
    struct PixelLine newPixelLine(
        int start_x, int start_y,
        int end_x, int end_y,
        u8 r = 0, u8 g = 0, u8 b = 0, u8 a = 255
    );

    void RenderPixelLine(
        ARE::Config* config,
        const struct PixelLine* line
    );

    // Pixel Rectangle

    struct PixelRect {
        struct ARE::Rect2 geometry;
        struct ARE::RGBA color;
    };

    struct PixelRect newPixelRect(
        struct ARE::Rect2 geometry,
        struct ARE::RGBA color
    );
    struct PixelRect newPixelRect(
        struct ARE::Vec2 origin,
        struct ARE::Vec2 size,
        float angle,
        struct ARE::RGBA color
    );
    struct PixelRect newPixelRect(
        int x = 0, int y = 0,
        int w = 0, int h = 0,
        float angle = 0,
        u8 r = 0, u8 g = 0, u8 b = 0, u8 a = 255
    );

    void RenderPixelRect(
        ARE::Config* config,
        const struct PixelRect* rect
    );

    // Pixel Curve

    struct PixelCurve {
        struct ARE::Curve2 geometry;
        struct ARE::RGBA color;
    };

    struct PixelCurve newPixelCurve(
        struct ARE::Curve2 geometry,
        struct ARE::RGBA color
    );
    struct PixelCurve newPixelCurve(
        struct ARE::Vec2 position,
        int radius,
        float openAngle,
        float angle,
        struct ARE::RGBA color
    );
    struct PixelCurve newPixelCurve(
        int x, int y,
        int radius,
        float openAngle,
        float angle,
        u8 r, u8 g, u8 b, u8 a
    );

    void RenderPixelCurve(
        ARE::Config* config,
        const struct PixelCurve* curve
    );
}
