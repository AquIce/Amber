#pragma once

#include <base.hpp>

namespace ADL {
    struct RGBA {
        u8 r;
        u8 g;
        u8 b;
        u8 a;
    };

    struct RGBA newRGBA(
        u8 r = 0, u8 g = 0, u8 b = 0, u8 a = 255
    );

    bool isSameRGBA(
        struct RGBA first,
        struct RGBA second
    );
}
