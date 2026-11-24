#include "matrix.hpp"
#include <algorithm>
#include <cassert>
#include <chrono>
#include <iostream>
#include <random>
#include <vector>

int main() {

    const unsigned int seed = 42;
    std::mt19937 gen(seed);
    std::uniform_real_distribution<float> dist(1, 1000);

    std::vector<float> aSmallValues(16384);
    std::generate(aSmallValues.begin(), aSmallValues.end(),
                  [&]() { return dist(gen); });

    std::vector<float> bSmallValues(16384);
    std::generate(bSmallValues.begin(), bSmallValues.end(),
                  [&]() { return dist(gen); });

    Matrix aSmall(128, 128, aSmallValues);
    Matrix bSmall(128, 128, bSmallValues);

    auto start = std::chrono::steady_clock::now();

    int executions = 1000;
    for (int i = 0; i < executions; i++) {
        Matrix cSmall = aSmall.mul(bSmall);
    }

    auto end = std::chrono::steady_clock::now();
    auto duration =
        std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    std::cout << executions << " executions of 128 x 128 matrices\n";
    std::cout << "Execution time: " << duration.count() << " ms";

    return 0;
}
