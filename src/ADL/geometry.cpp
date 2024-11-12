#include <ADL/geometry.hpp>

struct ADL::Vec2 ADL::newVec2(
    int x, int y
) {
    return { x, y };
}

struct ADL::Line2 ADL::newLine2(
    ADL::Vec2 start,
    ADL::Vec2 end
) {
    return { start, end };
}
struct ADL::Line2 ADL::newLine2(
    int start_x, int start_y,
    int end_x, int end_y
) {
    return ADL::newLine2(
        ADL::newVec2(start_x, start_y),
        ADL::newVec2(end_x, end_y)
    );
}

struct ADL::Rect2 ADL::newRect2(
    struct ADL::Vec2 origin,
    struct ADL::Vec2 size
) {
    return { origin, size };
}

struct ADL::Rect2 ADL::newRect2(
    int x, int y,
    int w, int h
) {
    return ADL::newRect2(
        ADL::newVec2(x, y),
        ADL::newVec2(w, h)
    );
}
