#include "matrix.hpp"
#include <benchmark/benchmark.h>

static void BM_Matmul(benchmark::State& state) {
    const auto n = state.range(0);

    Matrix a(n, n);
    Matrix b(n, n);

    for (auto _ : state) {
        Matrix out = a.mul(b);
        benchmark::DoNotOptimize(out);
    }
}

BENCHMARK(BM_Matmul)->Arg(64)->Arg(128)->Arg(256)->Arg(512)->Arg(1024)->Unit(
    benchmark::kMillisecond);
