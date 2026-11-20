#include <algorithm>
#include <cassert>
#include <chrono>
#include <iostream>
#include <random>
#include <vector>

class Matrix {

  private:
    std::size_t rows{};
    std::size_t cols{};
    std::vector<float> data;
    std::size_t size{};

  public:
    Matrix(std::size_t rows, std::size_t cols, std::vector<float> data)
        : rows{rows}, cols{cols}, size(rows * cols), data{data} {}

    Matrix(std::size_t rows, std::size_t cols)
        : rows{rows}, cols{cols}, size(rows * cols), data(rows * cols) {}

    void print() {
        for (int i = 0; i < this->size; i++) {
            std::cout << this->data[i];
            if (i + 1 != size) {
                std::cout << ", ";
            }
            if ((i + 1) % cols == 0) {
                std::cout << std::endl;
            }
        }
        std::cout << std::endl;
    }

    Matrix mul(const Matrix& b) {

        assert(cols == b.rows && "Incompatible dimensions");

        Matrix out(rows, b.cols);

        for (std::size_t i = 0; i < rows; i++) {
            for (std::size_t j = 0; j < b.cols; j++) {
                for (std::size_t k = 0; k < cols; k++) {
                    out.data[i * b.cols + j] +=
                        data[i * cols + k] * b.data[k * b.cols + j];
                }
            }
        }

        return out;
    }
};

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
