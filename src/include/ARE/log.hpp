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
        LogLevel level;
        struct ReturnCode code;
        std::string message;
    };

    struct Log newLog(
        LogLevel level,
        struct ReturnCode code,
        std::string message
    );

    NODISCARD ReturnCode log(
        Log l
    );
}
