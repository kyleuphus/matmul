#pragma once
#include <cstddef>
#include <random>
#include <vector>

class Matrix {

  private:
    std::size_t rows{};
    std::size_t cols{};
    std::vector<float> data;
    std::size_t size{};

  public:
    Matrix(std::size_t rows, std::size_t cols, std::vector<float> data);

    Matrix(std::size_t rows, std::size_t cols);

    void print() const;

    Matrix mul(const Matrix& b) const;
};
