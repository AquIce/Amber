#include <ARE/config.hpp>

struct ARE::Config ARE::newConfig(
    std::string name,
    struct Vec2 size
) {
    return {
        name,
        size,
        { nullptr, nullptr },
        std::vector<struct ARE::EventHandler>()
    };
}
