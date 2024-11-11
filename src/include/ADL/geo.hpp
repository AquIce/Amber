#pragma once

namespace ADL {
    struct Vec2 {
        int x;
        int y;
    };

    struct Vec2 newVec2(
        int x = 0, int y = 0
    );

    struct Rect2 {
        Vec2 origin;
        Vec2 size;
    };

    struct Rect2 newRect2(
        struct Vec2 origin,
        struct Vec2 size
    );
    struct Rect2 newRect2(
        int x = 0, int y = 0,
        int w = 1, int h = 1
    );
}
