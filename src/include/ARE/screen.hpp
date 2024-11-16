#pragma once

#include <ARE/geometry.hpp>
#include <ARE/color.hpp>
#include <ARE/config.hpp>

#include <base.hpp>

#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_render.h>

#include <array>
#include <cstddef>
#include <vector>

namespace ARE {

    // General Screen Render

    void ClearScreen(
        ARE::Config* config,
        struct ARE::RGBA rgba = newRGBA()
    );

    [[nodiscard]] bool ChangeRenderRGBA(
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

    void RenderPixelCurve(
        ARE::Config* config,
        const struct PixelCurve* curve
    );

    // Pixel Parabola

    struct PixelParabola {
        struct ARE::Parabola2 geometry;
        struct ARE::RGBA color;
    };

    struct PixelParabola newPixelParabola(
        struct ARE::Parabola2 geometry,
        struct ARE::RGBA color
    );

    void RenderPixelParabola(
        ARE::Config* config,
        const struct PixelParabola* parabola
    );

    // Pixel Trig

    struct PixelTrig {
        struct ARE::Trig2 geometry;
        struct ARE::RGBA color;
    };

    struct PixelTrig newPixelTrig(
        struct ARE::Trig2 geometry,
        struct ARE::RGBA color
    );

    void RenderPixelTrig(
        ARE::Config* config,
        const struct ARE::PixelTrig* trig
    );
}
