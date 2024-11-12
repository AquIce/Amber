#include <ADL/screen.hpp>

void ADL::ClearScreen(
    ADL::Config* config,
    struct ADL::RGBA rgba
) {
    SDL_SetRenderDrawColor(config->sdl.renderer, rgba.r, rgba.g, rgba.b, rgba.a);
    SDL_RenderClear(config->sdl.renderer);
}

NODISCARD bool ADL::ChangeRenderRGBA(
    ADL::Config* config,
    struct ADL::RGBA rgba
) {
    u8 r, g, b, a;
    SDL_GetRenderDrawColor(config->sdl.renderer, &r, &g, &b, &a);
    if(!ADL::isSameRGBA(rgba, ADL::newRGBA(r, g, b, a))) {
        SDL_SetRenderDrawColor(
            config->sdl.renderer,
            rgba.r, rgba.g, rgba.b, rgba.a
        );
        return false;
    }
    return true;
}

void ADL::Flush(
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

void ADL::RenderLine(
    ADL::Config* config,
    const struct ADL::PixelLine* line
) {
    float m = static_cast<float>(
        line->geometry.end.y - line->geometry.start.y
    ) / line->geometry.end.x - line->geometry.start.x;

    for(u32 x = line->geometry.start.x; x <= line->geometry.end.x; x++) {
        Pixel p = {
            ADL::newVec2(
                x,
                line->geometry.start.y + m * (x - line->geometry.start.x)
            ),
            line->color
        };
        ADL::RenderPixel(config, &p);
    }
}
