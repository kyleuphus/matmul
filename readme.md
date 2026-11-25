
## baseline:

```cpp
for (std::size_t i = 0; i < rows; i++) {
    for (std::size_t j = 0; j < b.cols; j++) {
        for (std::size_t k = 0; k < cols; k++) {
            out.data[i * b.cols + j] +=
                data[i * cols + k] * b.data[k * b.cols + j];
        }
    }
}
```

google benchmark results:
```text
Run on (10 X 24 MHz CPU s)
CPU Caches:
  L1 Data 64 KiB
  L1 Instruction 128 KiB
  L2 Unified 4096 KiB (x10)
Load Average: 2.15, 2.57, 3.11
---------------------------------------------------------
Benchmark               Time             CPU   Iterations
---------------------------------------------------------
BM_Matmul/64        0.110 ms        0.110 ms         6402
BM_Matmul/128       0.997 ms        0.997 ms          702
BM_Matmul/256        10.7 ms         10.7 ms           66
BM_Matmul/512        98.6 ms         98.5 ms            7
BM_Matmul/1024        887 ms          886 ms            1
```

### Benchmark Environment

- Hardware: Apple M4 Pro
- Compiler: Apple Clang
- Build system: CMake
- Build configuration: Release
- Compiler optimization flags: `-O3 -DNDEBUG`
- Benchmarking framework: Google Benchmark v1.9.4
- Matrix element type: `float` (FP32)
- Random seed: 42
