#pragma once

#include <array>
#include <cmath>
#include <vector>
#include <cstddef>

namespace ARE {

    // Vec2

    struct Vec2 {
        int x;
        int y;
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

    // Line2

    struct Line2 {
        Vec2 start;
        Vec2 end;
    };

    struct Line2 newLine2(
        Vec2 start,
        Vec2 end
    );

    std::vector<struct Vec2> GetLine2Pixels(
        const struct Line2* line
    );

    // Rect2

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

    std::array<struct Vec2, 4> GetRect2Corners(
        const struct Rect2* rect
    );

    std::array<struct Line2, 4> GetRect2Lines2(
        const struct Rect2* rect
    );

    // Curve2

    struct Curve2 {
        struct Vec2 position;
        int radius;
        float openAngle;
        float angle;
    };

    struct Curve2 newCurve2(
        struct Vec2 position,
        int radius,
        float openAngle = 2 * M_PI,
        float angle = 0
    );

    std::vector<struct Vec2> GetCurve2Points(
        const struct Curve2* curve
    );

    struct Parabola2 {
        struct Vec2 position;
        std::vector<float> coefficients;
        int limit_plus;
        int limit_minus;
    };

    struct Parabola2 newParabola2(
        struct Vec2 position,
        std::vector<float> coefficients,
        int limit_plus, int limit_minus
    );
    struct Parabola2 newParabola2(
        struct Vec2 position,
        std::vector<float> coefficients,
        int limit
    );

    std::vector<struct Vec2> GetParabola2Points(
        const struct Parabola2* parabola,
        int y_limit_plus,
        int y_limit_minus
    );
}
