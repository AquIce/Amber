#include <ADL/config.hpp>

struct ADL::Config ADL::newConfig(
    std::string name,
    struct Vec2 size
) {
    return {
        name,
        size,
        { nullptr, nullptr },
        std::vector<struct ADL::EventHandler>()
    };
}
