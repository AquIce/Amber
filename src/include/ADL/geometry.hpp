#pragma once

#include <array>
#include <cmath>
#include <vector>

namespace ADL {

    struct Vec2 {
        int x;
        int y;
    };

    struct Vec2F {
        float x;
        float y;
    };

    struct Vec2 newVec2(
        int x = 0, int y = 0
    );

    struct Vec2 AddVec2(
        struct Vec2 first,
        struct Vec2 second
    );

    struct Vec2 MultiplyVec2(
        struct Vec2 vec,
        float factor
    );

    struct Vec2 ReverseVec2(
        struct Vec2 vec
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

    std::vector<struct Vec2> GetLine2Pixels(
        const struct Line2* line
    );

    struct Rect2 {
        struct Vec2 origin;
        struct Vec2 size;
        float angle;
    };

    struct Rect2 newRect2(
        struct Vec2 origin,
        struct Vec2 size,
        float angle = 0
    );
    struct Rect2 newRect2(
        int x = 0, int y = 0,
        int w = 1, int h = 1,
        float angle = 0
    );

    std::array<Vec2, 4> GetRect2Corners(
        const struct Rect2* rect
    );

    std::array<Line2, 4> GetRect2Lines2(
        const struct Rect2* rect
    );
}
