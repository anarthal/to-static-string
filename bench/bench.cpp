#include <benchmark/benchmark.h>
#include <charconv>
#include <chrono>
#include <string>

#include "tostr/to_static_string.h"

const auto initial_i = std::chrono::system_clock::now().time_since_epoch().count();

static void benchmark_std_int(benchmark::State& state)
{
    // Setup
    auto i = initial_i;

    for (auto _ : state)
    {
        auto s = std::to_string(i++);
        benchmark::DoNotOptimize(s);
    }
}

static void benchmark_static_int(benchmark::State& state)
{
    // Setup
    auto i = initial_i;

    for (auto _ : state)
    {
        auto s = tostr::to_static_string(i);
        benchmark::DoNotOptimize(s);
    }
}
static void benchmark_std_double(benchmark::State& state)
{
    // Setup
    auto d = static_cast<double>(initial_i);

    for (auto _ : state)
    {
        auto s = std::to_string(d);
        benchmark::DoNotOptimize(s);
    }
}

static void benchmark_static_double(benchmark::State& state)
{
    // Setup
    auto d = static_cast<double>(initial_i);

    for (auto _ : state)
    {
        auto s = tostr::to_static_string(d);
        benchmark::DoNotOptimize(s);
    }
}

static void benchmark_static_int_tochars(benchmark::State& state)
{
    // Setup
    auto i = initial_i;

    for (auto _ : state)
    {
        char buff[32];
        auto r = std::to_chars(buff, buff + sizeof(buff), i);
        benchmark::DoNotOptimize(r);
    }
}

static void benchmark_static_double_tochars(benchmark::State& state)
{
    // Setup
    auto d = static_cast<double>(initial_i);

    for (auto _ : state)
    {
        char buff[32];
        auto r = std::to_chars(buff, buff + sizeof(buff), d);
        benchmark::DoNotOptimize(r);
    }
}

// Register the function as a benchmark
BENCHMARK(benchmark_std_int);
BENCHMARK(benchmark_static_int);
BENCHMARK(benchmark_std_double);
BENCHMARK(benchmark_static_double);
BENCHMARK(benchmark_static_int_tochars);
BENCHMARK(benchmark_static_double_tochars);
// Run the benchmark
BENCHMARK_MAIN();