#include <ADL/screen.hpp>

struct ADL::RGBA ADL::newRGBA(u8 r, u8 g, u8 b, u8 a) {
    return { r, g, b, a };
}

bool ADL::isSameRGBA(struct ADL::RGBA first, struct ADL::RGBA second) {
    return (
        first.r == second.r &&
        first.g == second.g &&
        first.b == second.b &&
        first.a == second.a
    );
}

void ADL::ClearScreen(ADL::Config* config, struct ADL::RGBA rgba) {
    SDL_SetRenderDrawColor(config->sdl.renderer, rgba.r, rgba.g, rgba.b, rgba.a);
    SDL_RenderClear(config->sdl.renderer);
}

NODISCARD bool ADL::ChangeRenderRGBA(ADL::Config* config, struct ADL::RGBA rgba) {
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

void ADL::Flush(ADL::Config* config) {
    SDL_RenderPresent(config->sdl.renderer);
}

struct ADL::Pixel ADL::newPixel(struct ADL::Vec2 position, struct ADL::RGBA color) {
    return {
        position,
        color
    };
}

struct ADL::Pixel ADL::newPixel(int x, int y, int r, int g, int b, int a) {
    return ADL::newPixel(
        ADL::newVec2(x, y),
        ADL::newRGBA(r, g, b, a)
    );
}

void ADL::RenderPixel(ADL::Config* config, const struct ADL::Pixel* pixel) {
    FORCE_DISCARD ADL::ChangeRenderRGBA(config, pixel->color);
    SDL_RenderDrawPoint(
        config->sdl.renderer,
        pixel->position.x, pixel->position.y
    );
}
