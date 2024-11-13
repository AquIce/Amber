#include <ADL/geometry.hpp>

struct ADL::Vec2 ADL::newVec2(
    int x, int y
) {
    return { x, y };
}

struct ADL::Vec2 ADL::AddVec2(
    struct ADL::Vec2 first,
    struct ADL::Vec2 second
) {
    return newVec2(
        first.x + second.x,
        first.y + second.y
    );
}

struct ADL::Vec2 ADL::MultiplyVec2(
    struct ADL::Vec2 vec,
    float factor
) {
    return newVec2(
        vec.x * factor,
        vec.y * factor
    );
}

struct ADL::Vec2 ADL::ReverseVec2(
    struct ADL::Vec2 vec
) {
    return ADL::newVec2(
        -vec.x, -vec.y
    );
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

std::vector<struct ADL::Vec2> ADL::GetLine2Pixels(
    const struct ADL::Line2* line
) {
    int x1 = line->start.x,
        y1 = line->start.y,
        x2 = line->end.x,
        y2 = line->end.y;

    std::vector<struct ADL::Vec2> linePixels;

    int dx = std::abs(x2 - x1);
    int dy = std::abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;

    while(true) {
        linePixels.push_back(ADL::newVec2(x1, y1));

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

struct ADL::Rect2 ADL::newRect2(
    struct ADL::Vec2 origin,
    struct ADL::Vec2 size,
    float angle
) {
    return { origin, size, angle };
}

struct ADL::Rect2 ADL::newRect2(
    int x, int y,
    int w, int h,
    float angle
) {
    return ADL::newRect2(
        ADL::newVec2(x, y),
        ADL::newVec2(w, h),
        angle
    );
}

std::array<struct ADL::Vec2, 4> ADL::GetRect2Corners(
    const struct ADL::Rect2* rect
) {
    return {
        ADL::newVec2(
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
        ADL::newVec2(
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
        ADL::newVec2(
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
        ADL::newVec2(
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

std::array<struct ADL::Line2, 4> ADL::GetRect2Lines2(
    const struct ADL::Rect2* rect
) {
    std::array<ADL::Vec2, 4> corners = ADL::GetRect2Corners(rect);

    return std::array<ADL::Line2, 4>({
        ADL::newLine2(corners[0], corners[1]),
        ADL::newLine2(corners[1], corners[2]),
        ADL::newLine2(corners[2], corners[3]),
        ADL::newLine2(corners[3], corners[0])
    });
}

struct ADL::Curve2 ADL::newCurve2(
    struct ADL::Vec2 position,
    int radius,
    float openAngle,
    float angle
) {
    return { position, radius, openAngle, angle };
}
struct ADL::Curve2 ADL::newCurve2(
    int x, int y,
    int radius,
    float openAngle,
    float angle
) {
    return ADL::newCurve2(
        ADL::newVec2(x, y),
        radius,
        openAngle,
        angle
    );
}

void ADL::AddCirclePoints(
    std::vector<struct ADL::Vec2>& points,
    struct ADL::Vec2 center,
    struct ADL::Vec2 offset
) {
    points.push_back(ADL::newVec2(
        center.x + offset.x,
        center.y + offset.y
    ));
    points.push_back(ADL::newVec2(
        center.x + offset.x,
        center.y - offset.y
    ));
    points.push_back(ADL::newVec2(
        center.x - offset.x,
        center.y + offset.y
    ));
    points.push_back(ADL::newVec2(
        center.x - offset.x,
        center.y - offset.y
    ));

    points.push_back(ADL::newVec2(
        center.x + offset.y,
        center.y + offset.x
    ));
    points.push_back(ADL::newVec2(
        center.x + offset.y,
        center.y - offset.x
    ));
    points.push_back(ADL::newVec2(
        center.x - offset.y,
        center.y + offset.x
    ));
    points.push_back(ADL::newVec2(
        center.x - offset.y,
        center.y - offset.x
    ));
}

std::vector<struct ADL::Vec2> ADL::GetCurve2Points(
    const struct ADL::Curve2* curve
) {
    std::vector<struct ADL::Vec2> points = {};

    struct ADL::Vec2 pos = ADL::newVec2(0, curve->radius);
    int d = 3 - 2 * curve->radius;

    ADL::AddCirclePoints(
        points, curve->position, pos
    );

    while(pos.y >= pos.x) {
        if(d > 0) {
            pos.y--;
            d += 4 * (pos.x - pos.y) + 10;
        } else {
            d += 4 * pos.x + 6;
        }

        pos.x++;

        ADL::AddCirclePoints(
            points, curve->position, pos
        );
    }

    return points;
}
