#include "ARE/geometry.hpp"
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
struct ARE::Pixel ARE::newPixel(
    int x, int y,
    int r, int g, int b, int a
) {
    return ARE::newPixel(
        ARE::newVec2(x, y),
        ARE::newRGBA(r, g, b, a)
    );
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
struct ARE::PixelLine ARE::newPixelLine(
    struct ARE::Vec2 start,
    struct ARE::Vec2 end,
    struct ARE::RGBA color
) {
    return ARE::newPixelLine(
        ARE::newLine2(start, end),
        color
    );
}
struct ARE::PixelLine ARE::newPixelLine(
    int start_x, int start_y,
    int end_x, int end_y,
    u8 r, u8 g, u8 b, u8 a
) {
    return ARE::newPixelLine(
        ARE::newVec2(start_x, start_y),
        ARE::newVec2(end_x, end_y),
        ARE::newRGBA(r, g, b, a)
    );
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
struct ARE::PixelRect ARE::newPixelRect(
    struct ARE::Vec2 origin,
    struct ARE::Vec2 size,
    float angle,
    struct ARE::RGBA color
) {
    return ARE::newPixelRect(
        ARE::newRect2(origin, size, angle),
        color
    );
}
struct ARE::PixelRect ARE::newPixelRect(
    int x, int y,
    int w, int h,
    float angle,
    u8 r, u8 g, u8 b, u8 a
) {
    return ARE::newPixelRect(
        ARE::newVec2(x, y),
        ARE::newVec2(w, h),
        angle,
        ARE::newRGBA(r, g, b, a)
    );
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
struct ARE::PixelCurve ARE::newPixelCurve(
    struct ARE::Vec2 position,
    int radius,
    float openAngle,
    float angle,
    struct ARE::RGBA color
) {
    return ARE::newPixelCurve(
        ARE::newCurve2(
            position,
            radius,
            openAngle,
            angle
        ),
        color
    );
}
struct ARE::PixelCurve ARE::newPixelCurve(
    int x, int y,
    int radius,
    float openAngle,
    float angle,
    u8 r, u8 g, u8 b, u8 a
) {
    return ARE::newPixelCurve(
        ARE::newVec2(x, y),
        radius,
        openAngle,
        angle,
        ARE::newRGBA(r, g, b, a)
    );
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
