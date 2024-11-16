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
        struct ARE::Vec2 geometry,
        struct ARE::RGBA color = ARE::newRGBA()
    );

    void RenderPixel(
        ARE::Config* config,
        const struct Pixel* pixel
    );

    // Pixel Line

    struct PixelLine {
        struct ARE::Line2 geometry;
        struct ARE::RGBA color;
        bool isStatic;
        std::vector<struct ARE::Vec2> points;
    };

    struct PixelLine newPixelLine(
        struct ARE::Line2 geometry,
        struct ARE::RGBA color = ARE::newRGBA(),
        bool isStatic = true
    );

    void RenderPixelLine(
        ARE::Config* config,
        struct PixelLine* line
    );

    // Pixel Rectangle

    struct PixelRect {
        struct ARE::Rect2 geometry;
        struct ARE::RGBA color;
        bool isStatic;
        std::vector<struct ARE::Vec2> points;
    };

    struct PixelRect newPixelRect(
        struct ARE::Rect2 geometry,
        struct ARE::RGBA color = ARE::newRGBA(),
        bool isStatic = true
    );

    void RenderPixelRect(
        ARE::Config* config,
        struct PixelRect* rect
    );

    // Pixel Curve

    struct PixelCurve {
        struct ARE::Curve2 geometry;
        struct ARE::RGBA color;
        bool isStatic;
        std::vector<struct ARE::Vec2> points;
    };

    struct PixelCurve newPixelCurve(
        struct ARE::Curve2 geometry,
        struct ARE::RGBA color = ARE::newRGBA(),
        bool isStatic = true
    );

    void RenderPixelCurve(
        ARE::Config* config,
        struct PixelCurve* curve
    );

    // Pixel Parabola

    struct PixelParabola {
        struct ARE::Parabola2 geometry;
        struct ARE::RGBA color;
        bool isStatic;
        std::vector<struct ARE::Vec2> points;
    };

    struct PixelParabola newPixelParabola(
        struct ARE::Parabola2 geometry,
        struct ARE::RGBA color = ARE::newRGBA(),
        bool isStatic = true
    );

    void RenderPixelParabola(
        ARE::Config* config,
        struct PixelParabola* parabola
    );

    // Pixel Trig

    struct PixelTrig {
        struct ARE::Trig2 geometry;
        struct ARE::RGBA color;
        bool isStatic;
        std::vector<struct ARE::Vec2> points;
    };

    struct PixelTrig newPixelTrig(
        struct ARE::Trig2 geometry,
        struct ARE::RGBA color = ARE::newRGBA(),
        bool isStatic = true
    );

    void RenderPixelTrig(
        ARE::Config* config,
        struct ARE::PixelTrig* trig
    );
}
