#pragma once

#include <base.hpp>

#include <iostream>
#include <string>
#include <cstdlib>

namespace ARE {

    enum class LogLevel {
        INFO = 0,
        WARNING,
        ERROR
    };

    struct ReturnCode {
        bool isExitCode;
        int exitCode;
    };

    struct ReturnCode newReturnCode(
        bool isExitCode = false,
        int exitCode = 0
    );

    struct Log {
        enum LogLevel level;
        struct ReturnCode code;
        std::string message;
    };

    struct Log newLog(
        enum LogLevel level,
        struct ReturnCode code,
        std::string message
    );

    [[nodiscard]] ReturnCode log(
        Log l
    );
}
