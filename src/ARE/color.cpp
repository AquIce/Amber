#include <ARE/color.hpp>

struct ARE::RGBA ARE::newRGBA(
    u8 r, u8 g, u8 b, u8 a
) {
    return { r, g, b, a };
}

bool ARE::isSameRGBA(
    struct ARE::RGBA first,
    struct ARE::RGBA second
) {
    return (
        first.r == second.r &&
        first.g == second.g &&
        first.b == second.b &&
        first.a == second.a
    );
}
