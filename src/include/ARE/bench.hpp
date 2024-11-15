#pragma once

#include <ARE/log.hpp>

#include <algorithm>
#include <chrono>
#include <cmath>
#include <numeric>
#include <string>
#include <vector>

namespace ARE {

    long long Duration(
        std::chrono::time_point<std::chrono::system_clock> start,
        std::chrono::time_point<std::chrono::system_clock> end
    );

    struct Benchmark {
        std::string name;
        std::vector<std::chrono::time_point<std::chrono::system_clock>> milestones;
    };

    struct Benchmark newBenchmark(
        std::string name
    );

    NODISCARD ARE::Log AddBenchmarkMilestone(
        struct Benchmark* benchmark,
        std::chrono::time_point<std::chrono::system_clock> milestone = std::chrono::system_clock::now()
    );

    struct BenchmarkStats {
        long long totalTime;
        long long maxTime;
        long long minTime;
        long long avgTime;
    };

    struct BenchmarkStats GetBenchmarkStats(
        struct Benchmark benchmark
    );

    void ShowBenchmarkStats(
        struct Benchmark benchmark
    );
}
