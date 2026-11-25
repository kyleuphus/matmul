#include "matrix.hpp"
#include <algorithm>
#include <cassert>
#include <iostream>
#include <utility>

Matrix::Matrix(std::size_t rows, std::size_t cols, std::vector<float> data)
    : rows{rows}, cols{cols}, data{std::move(data)}, size(rows * cols) {

    assert(this->data.size() == size && "Incompatible data size");
}

Matrix::Matrix(std::size_t rows, std::size_t cols)
    : rows{rows}, cols{cols}, data(rows * cols), size(rows * cols) {}

void Matrix::print() const {
    for (size_t i = 0; i < size; i++) {
        std::cout << data[i];
        if (i + 1 != size) {
            std::cout << ", ";
        }
        if ((i + 1) % cols == 0) {
            std::cout << std::endl;
        }
    }
    std::cout << std::endl;
}

Matrix Matrix::mul(const Matrix& b) const {

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
