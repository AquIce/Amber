#include <ARE/log.hpp>

struct ARE::ReturnCode ARE::newReturnCode(
    bool isExitCode,
    int exitCode
) {
    return { isExitCode, exitCode };
}

struct ARE::Log ARE::newLog(
    enum ARE::LogLevel level,
    struct ARE::ReturnCode code,
    std::string message
) {
    return { level, code, message };
}

NODISCARD ARE::ReturnCode ARE::log(
    ARE::Log l
) {
    switch(l.level) {
        case ARE::LogLevel::INFO:
            std::clog << "[LOG::INFO] " << l.message << "\n";
            return ARE::newReturnCode();
        case ARE::LogLevel::WARNING:
            std::clog << "[LOG::WARN] " << l.message << "\n";
            return ARE::newReturnCode();
        default: //case ARE::LogLevel::ERROR:
            std::cerr << "[LOG::ERROR] " << l.message << "\n";
            return ARE::newReturnCode(true, -1);
    }
}
