#include <ADL/screen.hpp>

struct ADL::RGBA ADL::newRGBA(u8 r, u8 g, u8 b, u8 a) {
    return { r, g, b, a };
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
