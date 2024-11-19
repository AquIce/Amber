#include <Amber/Log.hpp>

std::shared_ptr<spdlog::logger> Amber::Logger::engineLogger;
std::shared_ptr<spdlog::logger> Amber::Logger::clientLogger;

void Amber::Logger::Init() {
    spdlog::set_pattern("%^[%T] %n: %v%$");

    engineLogger = spdlog::stdout_color_mt("Amber");
    engineLogger->set_level(spdlog::level::trace);
    clientLogger = spdlog::stdout_color_mt("App");
    clientLogger->set_level(spdlog::level::trace);
}

inline std::shared_ptr<spdlog::logger>& Amber::Logger::GetEngineLogger() {
    return engineLogger;
}
inline std::shared_ptr<spdlog::logger>& Amber::Logger::GetClientLogger() {
    return clientLogger;
}
