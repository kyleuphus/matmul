#include "matrix.hpp"
#include <benchmark/benchmark.h>

Matrix randomMatrix(std::size_t rows, std::size_t cols, std::mt19937& gen) {

    std::uniform_real_distribution<float> dist(-1.0f, 1.0f);

    std::vector<float> values(rows * cols);

    std::generate(values.begin(), values.end(), [&]() { return dist(gen); });

    return Matrix(rows, cols, std::move(values));
}

static void BM_Matmul(benchmark::State& state) {
    const auto n = state.range(0);

    std::mt19937 gen(42);

    Matrix a = randomMatrix(n, n, gen);
    Matrix b = randomMatrix(n, n, gen);

    for (auto _ : state) {
        Matrix out = a.mul(b);
        benchmark::DoNotOptimize(out);
    }
}

BENCHMARK(BM_Matmul)->Arg(64)->Arg(128)->Arg(256)->Arg(512)->Arg(1024)->Unit(
    benchmark::kMillisecond);
