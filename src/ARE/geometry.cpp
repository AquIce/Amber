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

std::vector<struct ARE::Vec2> ARE::GetLine2Points(
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

std::vector<struct ARE::Vec2> ARE::GetRect2Points(
    const struct ARE::Rect2* rect
) {
    std::vector<struct ARE::Vec2> points;

    std::array<struct ARE::Line2, 4> lines = ARE::GetRect2Lines2(rect);

    for(const struct ARE::Line2& line : lines) {
        std::vector<struct ARE::Vec2> linePoints = ARE::GetLine2Points(&line);
        points.insert(
            points.end(),
            linePoints.begin(),
            linePoints.end()
        );
    }

    return points;
}

struct ARE::Curve2 ARE::newCurve2(
    struct ARE::Vec2 position,
    int radius,
    float openAngle,
    float angle
) {
    return { position, radius, openAngle, angle };
}

std::vector<struct ARE::Vec2> ARE::GetCurve2Points(
    const struct ARE::Curve2* curve
) {
    std::vector<struct ARE::Vec2> points = {};

    float angleIncrement = M_PI / curve->radius / 4;

    float openAngle = curve->openAngle > static_cast<float>(2 * M_PI) ?
        static_cast<float>(2 * M_PI) :
        curve->openAngle;

    for(
        float currentAngle = curve->angle;
        currentAngle < curve->angle + openAngle;
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

struct ARE::Parabola2 ARE::newParabola2(
    struct ARE::Vec2 position,
    std::vector<float> coefficients,
    struct ARE::Vec2 max,
    struct ARE::Vec2 min
) {
    return {
        position,
        coefficients,
        max,
        min
    };
}

std::vector<struct ARE::Vec2> ARE::GetParabola2Points(
    const struct ARE::Parabola2* parabola
) {
    std::vector<struct ARE::Vec2> points = {};

    float last_y = 0;
    float offset = 1;
    bool plus_in = true;
    bool minus_in = true;

    for(
        float x = 0;
        x < std::max(
            std::abs(parabola->min.x),
            std::abs(parabola->max.x)
        ) && (plus_in || minus_in);
        x += offset
    ) {
        float y = 0;
        for(
            size_t exponent = 0;
            exponent < parabola->coefficients.size();
            exponent++
        ) {
            y += std::pow(x, exponent) * parabola->coefficients[exponent];
        }
        if(last_y != 0 && y - last_y > 1) {
            offset = static_cast<float>(0.1) / (y - last_y);
        }
        last_y = y;

        if(minus_in && x >= parabola->min.x) {
            struct ARE::Vec2 pos = ARE::newVec2(
                parabola->position.x - std::round(x),
                parabola->position.y + std::round(y)
            );

            if(pos.y > parabola->max.y) {
                if(
                    parabola->coefficients.size() % 2 != 0 &&
                    parabola->coefficients.at(0) < 0
                ) {
                    points.push_back(pos);
                    continue;
                }
                minus_in = false;
            }
            points.push_back(pos);
        }
        if(plus_in && x <= parabola->max.x) {
            struct ARE::Vec2 pos = ARE::newVec2(
                parabola->position.x + std::round(x),
                parabola->position.y - std::round(y)
            );

            if(pos.y < parabola->min.y) {
                if(
                    parabola->coefficients.size() % 2 != 0 &&
                    parabola->coefficients.at(0) < 0
                ) {
                    points.push_back(pos);
                    continue;
                }
                plus_in = false;
            }
            points.push_back(pos);
        }
    }

    return points;
}

struct ARE::Trig2 ARE::newTrig2(
    struct ARE::Vec2 position,
    enum ARE::TrigType type,
    float coefficient,
    int limit_plus,
    int limit_minus
) {
    return {
        position,
        type,
        coefficient,
        limit_plus,
        limit_minus
    };
}

std::vector<struct ARE::Vec2> ARE::GetTrig2Points(
    const struct ARE::Trig2* trig
) {
    std::vector<struct ARE::Vec2> points = {};

    std::function<float (float)> trigFn;
    switch(trig->type) {
        case ARE::TrigType::SIN:
            trigFn = (float (*)(float))&std::sin;
            break;
        case ARE::TrigType::COS:
            trigFn = (float (*)(float))&std::cos;
            break;
        case ARE::TrigType::TAN:
            trigFn = (float (*)(float))&std::tan;
            break;
        case ARE::TrigType::SEC:
            trigFn = [] (float angle) -> float {
                return static_cast<float>(1) / std::sin(angle);
            };
            break;
        case ARE::TrigType::CSC:
            trigFn = [] (float angle) -> float {
                return static_cast<float>(1) / std::cos(angle);
            };
            break;
        default: //case ARE::TrigType::COT:
            trigFn = [] (float angle) -> float {
                return static_cast<float>(1) / std::tan(angle);
            };
            break;
    }

    float offset = std::abs(trigFn(1.1) - trigFn(0.1)) / trig->coefficient;

    for(
        float x = trig->limit_minus;
        x < trig->limit_plus;
        x += offset
    ) {
        float y = trig->coefficient * trigFn(x);

        struct ARE::Vec2 pos = ARE::newVec2(
            trig->position.x - std::round(x),
            trig->position.y + std::round(y)
        );

        points.push_back(pos);
    }

    return points;
}
