#include <ADL/screen.hpp>

void ADL::ClearScreen(
    ADL::Config* config,
    struct ADL::RGBA rgba
) {
    SDL_SetRenderDrawColor(
        config->sdl.renderer,
        rgba.r, rgba.g, rgba.b, rgba.a
    );
    SDL_RenderClear(config->sdl.renderer);
}

NODISCARD bool ADL::ChangeRenderRGBA(
    ADL::Config* config,
    struct ADL::RGBA rgba
) {
    u8 r, g, b, a;
    SDL_GetRenderDrawColor(
        config->sdl.renderer,
        &r, &g, &b, &a
    );
    if(!ADL::isSameRGBA(rgba, ADL::newRGBA(r, g, b, a))) {
        SDL_SetRenderDrawColor(
            config->sdl.renderer,
            rgba.r, rgba.g, rgba.b, rgba.a
        );
        return false;
    }
    return true;
}

void ADL::PushRender(
    ADL::Config* config
) {
    SDL_RenderPresent(config->sdl.renderer);
}

struct ADL::Pixel ADL::newPixel(
    struct ADL::Vec2 position,
    struct ADL::RGBA color
) {
    return {
        position,
        color
    };
}
struct ADL::Pixel ADL::newPixel(
    int x, int y,
    int r, int g, int b, int a
) {
    return ADL::newPixel(
        ADL::newVec2(x, y),
        ADL::newRGBA(r, g, b, a)
    );
}

void ADL::RenderPixel(
    ADL::Config* config,
    const struct ADL::Pixel* pixel
) {
    FORCE_DISCARD ADL::ChangeRenderRGBA(config, pixel->color);
    SDL_RenderDrawPoint(
        config->sdl.renderer,
        pixel->geometry.x, pixel->geometry.y
    );
}

struct ADL::PixelLine ADL::newPixelLine(
    struct ADL::Line2 line,
    struct ADL::RGBA color
) {
    return {
        line,
        color
    };
}
struct ADL::PixelLine ADL::newPixelLine(
    struct ADL::Vec2 start,
    struct ADL::Vec2 end,
    struct ADL::RGBA color
) {
    return ADL::newPixelLine(
        ADL::newLine2(start, end),
        color
    );
}
struct ADL::PixelLine ADL::newPixelLine(
    int start_x, int start_y,
    int end_x, int end_y,
    u8 r, u8 g, u8 b, u8 a
) {
    return ADL::newPixelLine(
        ADL::newVec2(start_x, start_y),
        ADL::newVec2(end_x, end_y),
        ADL::newRGBA(r, g, b, a)
    );
}

void ADL::RenderPixelLine(
    ADL::Config* config,
    const struct ADL::PixelLine* line
) {
    std::vector<ADL::Vec2> linePixels = ADL::GetLine2Pixels(&line->geometry);
    for(const auto& pixel : linePixels) {
        struct ADL::Pixel p = {
            pixel,
            line->color
        };
        ADL::RenderPixel(config, &p);
    }
}

struct ADL::PixelRect ADL::newPixelRect(
    struct ADL::Rect2 geometry,
    struct ADL::RGBA color
) {
    return { geometry, color };
}
struct ADL::PixelRect ADL::newPixelRect(
    struct ADL::Vec2 origin,
    struct ADL::Vec2 size,
    float angle,
    struct ADL::RGBA color
) {
    return ADL::newPixelRect(
        ADL::newRect2(origin, size, angle),
        color
    );
}
struct ADL::PixelRect ADL::newPixelRect(
    int x, int y,
    int w, int h,
    float angle,
    u8 r, u8 g, u8 b, u8 a
) {
    return ADL::newPixelRect(
        ADL::newVec2(x, y),
        ADL::newVec2(w, h),
        angle,
        ADL::newRGBA(r, g, b, a)
    );
}

void ADL::RenderPixelRect(
    ADL::Config* config,
    const struct ADL::PixelRect* rect
) {
    Pixel p = {
        rect->geometry.origin,
        ADL::newRGBA(255, 255, 255, 255)
    };
    ADL::RenderPixel(config, &p);

    std::array<ADL::Line2, 4> lines = ADL::GetRect2Lines2(&rect->geometry);
    for(const auto& line : lines) {
        ADL::PixelLine pLine = ADL::newPixelLine(
            line,
            ADL::newRGBA(255, 0, 0, 255)
        );
        ADL::RenderPixelLine(
            config,
            &pLine
        );
    }
}

struct ADL::PixelCurve ADL::newPixelCurve(
    struct ADL::Curve2 geometry,
    struct ADL::RGBA color
) {
    return { geometry, color };
}
struct ADL::PixelCurve ADL::newPixelCurve(
    struct ADL::Vec2 position,
    int radius,
    float openAngle,
    float angle,
    struct ADL::RGBA color
) {
    return ADL::newPixelCurve(
        ADL::newCurve2(
            position,
            radius,
            openAngle,
            angle
        ),
        color
    );
}
struct ADL::PixelCurve ADL::newPixelCurve(
    int x, int y,
    int radius,
    float openAngle,
    float angle,
    u8 r, u8 g, u8 b, u8 a
) {
    return ADL::newPixelCurve(
        ADL::newVec2(x, y),
        radius,
        openAngle,
        angle,
        ADL::newRGBA(r, g, b, a)
    );
}

void ADL::RenderPixelCurve(
    ADL::Config* config,
    const struct ADL::PixelCurve curve
) {

}
