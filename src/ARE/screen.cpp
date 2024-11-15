#include <ARE/screen.hpp>

void ARE::ClearScreen(
    ARE::Config* config,
    struct ARE::RGBA rgba
) {
    SDL_SetRenderDrawColor(
        config->sdl.renderer,
        rgba.r, rgba.g, rgba.b, rgba.a
    );
    SDL_RenderClear(config->sdl.renderer);
}

NODISCARD bool ARE::ChangeRenderRGBA(
    ARE::Config* config,
    struct ARE::RGBA rgba
) {
    u8 r, g, b, a;
    SDL_GetRenderDrawColor(
        config->sdl.renderer,
        &r, &g, &b, &a
    );
    if(!ARE::isSameRGBA(rgba, ARE::newRGBA(r, g, b, a))) {
        SDL_SetRenderDrawColor(
            config->sdl.renderer,
            rgba.r, rgba.g, rgba.b, rgba.a
        );
        return false;
    }
    return true;
}

void ARE::PushRender(
    ARE::Config* config
) {
    SDL_RenderPresent(config->sdl.renderer);
}

struct ARE::Pixel ARE::newPixel(
    struct ARE::Vec2 position,
    struct ARE::RGBA color
) {
    return {
        position,
        color
    };
}

void ARE::RenderPixel(
    ARE::Config* config,
    const struct ARE::Pixel* pixel
) {
    FORCE_DISCARD ARE::ChangeRenderRGBA(config, pixel->color);
    SDL_RenderDrawPoint(
        config->sdl.renderer,
        pixel->geometry.x, pixel->geometry.y
    );
}

struct ARE::PixelLine ARE::newPixelLine(
    struct ARE::Line2 line,
    struct ARE::RGBA color
) {
    return {
        line,
        color
    };
}

void ARE::RenderPixelLine(
    ARE::Config* config,
    const struct ARE::PixelLine* line
) {
    std::vector<ARE::Vec2> linePixels = ARE::GetLine2Pixels(&line->geometry);
    for(const auto& pixel : linePixels) {
        struct ARE::Pixel p = {
            pixel,
            line->color
        };
        ARE::RenderPixel(config, &p);
    }
}

struct ARE::PixelRect ARE::newPixelRect(
    struct ARE::Rect2 geometry,
    struct ARE::RGBA color
) {
    return { geometry, color };
}

void ARE::RenderPixelRect(
    ARE::Config* config,
    const struct ARE::PixelRect* rect
) {
    Pixel p = {
        rect->geometry.origin,
        ARE::newRGBA(255, 255, 255, 255)
    };
    ARE::RenderPixel(config, &p);

    std::array<struct ARE::Line2, 4> lines = ARE::GetRect2Lines2(
        &rect->geometry
    );
    for(const auto& line : lines) {
        ARE::PixelLine pLine = ARE::newPixelLine(
            line,
            ARE::newRGBA(255, 0, 0, 255)
        );
        ARE::RenderPixelLine(
            config,
            &pLine
        );
    }
}

struct ARE::PixelCurve ARE::newPixelCurve(
    struct ARE::Curve2 geometry,
    struct ARE::RGBA color
) {
    return { geometry, color };
}

void ARE::RenderPixelCurve(
    ARE::Config* config,
    const struct ARE::PixelCurve* curve
) {
    std::vector<struct ARE::Vec2> points = ARE::GetCurve2Points(
        &curve->geometry
    );
    for(const struct ARE::Vec2& point : points) {
        struct ARE::Pixel pixel = ARE::newPixel(
            point,
            curve->color
        );
        ARE::RenderPixel(config, &pixel);
    }
}

struct ARE::PixelParabola ARE::newPixelParabola(
    struct ARE::Parabola2 geometry,
    struct ARE::RGBA color
) {
    return { geometry, color };
}

void ARE::RenderPixelParabola(
    ARE::Config* config,
    const struct ARE::PixelParabola* parabola
) {
    std::vector<struct ARE::Vec2> points = ARE::GetParabola2Points(
        &parabola->geometry,
        config->size.y, 0
    );
    for(const struct ARE::Vec2& point : points) {
        struct ARE::Pixel pixel = ARE::newPixel(
            point,
            parabola->color
        );
        ARE::RenderPixel(config, &pixel);
    }
}
