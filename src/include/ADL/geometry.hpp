#pragma once

namespace ADL {
    struct Vec2 {
        int x;
        int y;
    };

    struct Vec2 newVec2(
        int x = 0, int y = 0
    );

    struct Line2 {
        Vec2 start;
        Vec2 end;
    };

    struct Line2 newLine2(
        Vec2 start,
        Vec2 end
    );
    struct Line2 newLine2(
        int start_x = 0, int start_y = 0,
        int end_x = 1, int end_y = 1
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
