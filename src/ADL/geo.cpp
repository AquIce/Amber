#include <ADL/geo.hpp>

struct ADL::Vec2 ADL::newVec2(int x, int y) {
    return { x, y };
}

struct ADL::Rect2 ADL::newRect2(struct ADL::Vec2 origin, struct ADL::Vec2 size) {
    return { origin, size };
}

struct ADL::Rect2 ADL::newRect2(int x, int y, int w, int h) {
    return ADL::newRect2(
        ADL::newVec2(x, y),
        ADL::newVec2(w, h)
    );
}
