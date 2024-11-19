#pragma once

#include <memory>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace Amber {
    class Logger {
    public:
        static void Init();

        inline static std::shared_ptr<spdlog::logger>& GetEngineLogger();
        inline static std::shared_ptr<spdlog::logger>& GetClientLogger();

    private:
        static std::shared_ptr<spdlog::logger> engineLogger;
        static std::shared_ptr<spdlog::logger> clientLogger;
    };
}
