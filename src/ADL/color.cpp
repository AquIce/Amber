#include <ADL/color.hpp>

struct ADL::RGBA ADL::newRGBA(
    u8 r, u8 g, u8 b, u8 a
) {
    return { r, g, b, a };
}

bool ADL::isSameRGBA(
    struct ADL::RGBA first,
    struct ADL::RGBA second
) {
    return (
        first.r == second.r &&
        first.g == second.g &&
        first.b == second.b &&
        first.a == second.a
    );
}
