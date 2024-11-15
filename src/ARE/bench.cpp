#include "ARE/log.hpp"
#include <ARE/bench.hpp>

long long ARE::Duration(
    std::chrono::time_point<std::chrono::system_clock> start,
    std::chrono::time_point<std::chrono::system_clock> end
) {
    return std::chrono::duration_cast<std::chrono::milliseconds>(
        end - start
    ).count();
}

struct ARE::Benchmark ARE::newBenchmark(
    std::string name
) {
    return {
        name,
        std::vector<std::chrono::time_point<std::chrono::system_clock>>()
    };
}

NODISCARD ARE::Log ARE::AddBenchmarkMilestone(
    struct ARE::Benchmark* benchmark,
    std::chrono::time_point<std::chrono::system_clock> milestone
) {
    benchmark->milestones.push_back(milestone);

    return ARE::newLog(
        ARE::LogLevel::INFO,
        ARE::newReturnCode(false),
        std::to_string(
            benchmark->milestones.size() > 1 ?
                static_cast<int>(
                    std::round(
                        static_cast<float>(1000) /
                        ARE::Duration(
                            benchmark->milestones.at(
                                benchmark->milestones.size() - 2
                            ),
                            benchmark->milestones.back()
                        )
                    )
                ) :
                0
        ) + " FPS"
    );
}

struct ARE::BenchmarkStats ARE::GetBenchmarkStats(
    struct ARE::Benchmark benchmark
) {
    std::vector<long long> times = {};
    for(int i = 1; i < benchmark.milestones.size(); i++) {
        times.push_back(
            ARE::Duration(
                benchmark.milestones.at(i - 1),
                benchmark.milestones.at(i)
            )
        );
    }
    std::pair<
        std::vector<long long>::iterator,
        std::vector<long long>::iterator
    > minMax = std::minmax_element(
        times.begin(),
        times.end()
    );
    long long totalTime = std::accumulate(
        times.begin(),
        times.end(),
        0
    );
    return {
        totalTime,
        *minMax.second,
        *minMax.first,
        static_cast<long long>(
            std::round(
                static_cast<float>(totalTime) / times.size()
            )
        )
    };
}

void ARE::ShowBenchmarkStats(
    struct ARE::Benchmark benchmark
) {
    struct ARE::BenchmarkStats stats = ARE::GetBenchmarkStats(benchmark);

    FORCE_DISCARD ARE::log(
        ARE::newLog(
            ARE::LogLevel::INFO,
            ARE::newReturnCode(),
            std::string("\n\tTotal delta time:\t") + std::to_string(stats.totalTime) +
            "\tms\n\tMax delta time:\t\t" + std::to_string(stats.maxTime) +
            "\tms\n\tMin delta time:\t\t" + std::to_string(stats.minTime) +
            "\tms\n\tAverage delta time:\t" + std::to_string(stats.avgTime) + "\tms"
        )
    );
}
