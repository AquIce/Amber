#include <ARE/geometry.hpp>

struct ARE::Vec2 ARE::newVec2(
    int x, int y
) {
    return { x, y };
}

struct ARE::Vec2 ARE::AddVec2(
    struct ARE::Vec2 first,
    struct ARE::Vec2 second
) {
    return newVec2(
        first.x + second.x,
        first.y + second.y
    );
}

struct ARE::Vec2 ARE::MultiplyVec2(
    struct ARE::Vec2 vec,
    float factor
) {
    return newVec2(
        vec.x * factor,
        vec.y * factor
    );
}

struct ARE::Vec2 ARE::ReverseVec2(
    struct ARE::Vec2 vec
) {
    return ARE::newVec2(
        -vec.x, -vec.y
    );
}

struct ARE::Line2 ARE::newLine2(
    ARE::Vec2 start,
    ARE::Vec2 end
) {
    return { start, end };
}
struct ARE::Line2 ARE::newLine2(
    int start_x, int start_y,
    int end_x, int end_y
) {
    return ARE::newLine2(
        ARE::newVec2(start_x, start_y),
        ARE::newVec2(end_x, end_y)
    );
}

std::vector<struct ARE::Vec2> ARE::GetLine2Pixels(
    const struct ARE::Line2* line
) {
    int x1 = line->start.x,
        y1 = line->start.y,
        x2 = line->end.x,
        y2 = line->end.y;

    std::vector<struct ARE::Vec2> linePixels;

    int dx = std::abs(x2 - x1);
    int dy = std::abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;

    while(true) {
        linePixels.push_back(ARE::newVec2(x1, y1));

        if(x1 == x2 && y1 == y2) {
            break;
        }

        int e2 = 2 * err;

        if(e2 > -dy) {
            err -= dy;
            x1 += sx;
        }
        if(e2 < dx) {
            err += dx;
            y1 += sy;
        }
    }

    return linePixels;
}

struct ARE::Rect2 ARE::newRect2(
    struct ARE::Vec2 origin,
    struct ARE::Vec2 size,
    float angle
) {
    return { origin, size, angle };
}

struct ARE::Rect2 ARE::newRect2(
    int x, int y,
    int w, int h,
    float angle
) {
    return ARE::newRect2(
        ARE::newVec2(x, y),
        ARE::newVec2(w, h),
        angle
    );
}

std::array<struct ARE::Vec2, 4> ARE::GetRect2Corners(
    const struct ARE::Rect2* rect
) {
    return {
        ARE::newVec2(
            std::round(
                rect->origin.x +
                (static_cast<float>(rect->size.x) / 2) * std::cos(rect->angle) -
                (static_cast<float>(rect->size.y) / 2) * std::sin(rect->angle)
            ),
            std::round(
                rect->origin.y +
                (static_cast<float>(rect->size.x) / 2) * std::sin(rect->angle) +
                (static_cast<float>(rect->size.y) / 2) * std::cos(rect->angle)
            )
        ),
        ARE::newVec2(
            std::round(
                rect->origin.x -
                (static_cast<float>(rect->size.x) / 2) * std::cos(rect->angle) -
                (static_cast<float>(rect->size.y) / 2) * std::sin(rect->angle)
            ),
            std::round(
                rect->origin.y -
                (static_cast<float>(rect->size.x) / 2) * std::sin(rect->angle) +
                (static_cast<float>(rect->size.y) / 2) * std::cos(rect->angle)
            )
        ),
        ARE::newVec2(
            std::round(
                rect->origin.x -
                (static_cast<float>(rect->size.x) / 2) * std::cos(rect->angle) +
                (static_cast<float>(rect->size.y) / 2) * std::sin(rect->angle)
            ),
            std::round(
                rect->origin.y -
                (static_cast<float>(rect->size.x) / 2) * std::sin(rect->angle) -
                (static_cast<float>(rect->size.y) / 2) * std::cos(rect->angle)
            )
        ),
        ARE::newVec2(
            std::round(
                rect->origin.x +
                (static_cast<float>(rect->size.x) / 2) * std::cos(rect->angle) +
                (static_cast<float>(rect->size.y) / 2) * std::sin(rect->angle)
            ),
            std::round(
                rect->origin.y +
                (static_cast<float>(rect->size.x) / 2) * std::sin(rect->angle) -
                (static_cast<float>(rect->size.y) / 2) * std::cos(rect->angle)
            )
        )
    };
}

std::array<struct ARE::Line2, 4> ARE::GetRect2Lines2(
    const struct ARE::Rect2* rect
) {
    std::array<ARE::Vec2, 4> corners = ARE::GetRect2Corners(rect);

    return std::array<ARE::Line2, 4>({
        ARE::newLine2(corners[0], corners[1]),
        ARE::newLine2(corners[1], corners[2]),
        ARE::newLine2(corners[2], corners[3]),
        ARE::newLine2(corners[3], corners[0])
    });
}

struct ARE::Curve2 ARE::newCurve2(
    struct ARE::Vec2 position,
    int radius,
    float openAngle,
    float angle
) {
    return { position, radius, openAngle, angle };
}
struct ARE::Curve2 ARE::newCurve2(
    int x, int y,
    int radius,
    float openAngle,
    float angle
) {
    return ARE::newCurve2(
        ARE::newVec2(x, y),
        radius,
        openAngle,
        angle
    );
}

void ARE::AddCirclePoints(
    std::vector<struct ARE::Vec2>& points,
    struct ARE::Vec2 center,
    struct ARE::Vec2 offset
) {
    points.push_back(ARE::newVec2(
        center.x + offset.x,
        center.y + offset.y
    ));
    points.push_back(ARE::newVec2(
        center.x + offset.x,
        center.y - offset.y
    ));
    points.push_back(ARE::newVec2(
        center.x - offset.x,
        center.y + offset.y
    ));
    points.push_back(ARE::newVec2(
        center.x - offset.x,
        center.y - offset.y
    ));

    points.push_back(ARE::newVec2(
        center.x + offset.y,
        center.y + offset.x
    ));
    points.push_back(ARE::newVec2(
        center.x + offset.y,
        center.y - offset.x
    ));
    points.push_back(ARE::newVec2(
        center.x - offset.y,
        center.y + offset.x
    ));
    points.push_back(ARE::newVec2(
        center.x - offset.y,
        center.y - offset.x
    ));
}

std::vector<struct ARE::Vec2> ARE::GetCurve2Points(
    const struct ARE::Curve2* curve
) {
    std::vector<struct ARE::Vec2> points = {};

    float angleIncrement = M_PI / curve->radius / 4;

    for(
        float currentAngle = curve->angle;
        currentAngle < curve->angle + curve->openAngle;
        currentAngle += angleIncrement
    ) {
        struct ARE::Vec2 pos = ARE::newVec2(
            curve->position.x + std::round(std::cos(currentAngle) * curve->radius),
            curve->position.y - std::round(std::sin(currentAngle) * curve->radius)
        );

        points.push_back(pos);
    }

    return points;
}
