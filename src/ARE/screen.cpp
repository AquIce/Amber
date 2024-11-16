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

[[nodiscard]] bool ARE::ChangeRenderRGBA(
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
    struct ARE::Vec2 geometry,
    struct ARE::RGBA color
) {
    return {
        geometry,
        color
    };
}

void ARE::RenderPixel(
    ARE::Config* config,
    const struct ARE::Pixel* pixel
) {
    (void)ARE::ChangeRenderRGBA(config, pixel->color);
    SDL_RenderDrawPoint(
        config->sdl.renderer,
        pixel->geometry.x, pixel->geometry.y
    );
}

struct ARE::PixelLine ARE::newPixelLine(
    struct ARE::Line2 geometry,
    struct ARE::RGBA color,
    bool isStatic
) {
    return {
        geometry,
        color,
        isStatic,
        ARE::GetLine2Points(&geometry)
    };
}

void ARE::RenderPixelLine(
    ARE::Config* config,
    struct ARE::PixelLine* line
) {
    if(!line->isStatic) {
        line->points = ARE::GetLine2Points(&line->geometry);
    }
    for(const struct ARE::Vec2& point : line->points) {
        struct ARE::Pixel pixel = {
            point,
            line->color
        };
        ARE::RenderPixel(config, &pixel);
    }
}

struct ARE::PixelRect ARE::newPixelRect(
    struct ARE::Rect2 geometry,
    struct ARE::RGBA color,
    bool isStatic
) {
    return {
        geometry,
        color,
        isStatic,
        ARE::GetRect2Points(&geometry)
    };
}

void ARE::RenderPixelRect(
    ARE::Config* config,
    struct ARE::PixelRect* rect
) {
    if(!rect->isStatic) {
        rect->points = ARE::GetRect2Points(&rect->geometry);
    }
    for(const struct ARE::Vec2& point : rect->points) {
        struct ARE::Pixel pixel = {
            point,
            rect->color
        };
        ARE::RenderPixel(config, &pixel);
    }
}

struct ARE::PixelCurve ARE::newPixelCurve(
    struct ARE::Curve2 geometry,
    struct ARE::RGBA color,
    bool isStatic
) {
    return {
        geometry,
        color,
        isStatic,
        ARE::GetCurve2Points(&geometry)
    };
}

void ARE::RenderPixelCurve(
    ARE::Config* config,
    struct ARE::PixelCurve* curve
) {
    if(!curve->isStatic) {
        curve->points = ARE::GetCurve2Points(&curve->geometry);
    }
    for(const struct ARE::Vec2& point : curve->points) {
        struct ARE::Pixel pixel = {
            point,
            curve->color
        };
        ARE::RenderPixel(config, &pixel);
    }
}

struct ARE::PixelParabola ARE::newPixelParabola(
    struct ARE::Parabola2 geometry,
    struct ARE::RGBA color,
    bool isStatic
) {
    return {
        geometry,
        color,
        isStatic,
        ARE::GetParabola2Points(&geometry)
    };
}

void ARE::RenderPixelParabola(
    ARE::Config* config,
    struct ARE::PixelParabola* parabola
) {
    if(!parabola->isStatic) {
        parabola->points = ARE::GetParabola2Points(&parabola->geometry);
    }
    for(const struct ARE::Vec2& point : parabola->points) {
        struct ARE::Pixel pixel = {
            point,
            parabola->color
        };
        ARE::RenderPixel(config, &pixel);
    }
}

struct ARE::PixelTrig ARE::newPixelTrig(
    struct ARE::Trig2 geometry,
    struct ARE::RGBA color,
    bool isStatic
) {
    return {
        geometry,
        color,
        isStatic,
        ARE::GetTrig2Points(&geometry)
    };
}

void ARE::RenderPixelTrig(
    ARE::Config* config,
    struct ARE::PixelTrig* trig
) {
    if(!trig->isStatic) {
        trig->points = ARE::GetTrig2Points(&trig->geometry);
    }
    for(const struct ARE::Vec2& point : trig->points) {
        struct ARE::Pixel pixel = {
            point,
            trig->color
        };
        ARE::RenderPixel(config, &pixel);
    }
}
