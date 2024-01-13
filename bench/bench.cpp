#include <benchmark/benchmark.h>
#include <chrono>
#include <cstdlib>
#include <string>

#include "tostr/to_static_string.h"

const auto initial_i = std::chrono::system_clock::now().time_since_epoch().count();

static void benchmark_std(benchmark::State& state)
{
    // Setup
    auto i = initial_i;

    for (auto _ : state)
    {
        auto s = std::to_string(i++);
        benchmark::DoNotOptimize(s);
    }
}

static void benchmark_static(benchmark::State& state)
{
    // Setup
    auto i = initial_i;

    for (auto _ : state)
    {
        auto s = tostr::to_static_string(i);
        benchmark::DoNotOptimize(s);
    }
}

// Register the function as a benchmark
BENCHMARK(benchmark_std);
BENCHMARK(benchmark_static);

// Run the benchmark
BENCHMARK_MAIN();