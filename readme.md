
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

Run on (10 X 24 MHz CPU s)
CPU Caches:
  L1 Data 64 KiB
  L1 Instruction 128 KiB
  L2 Unified 4096 KiB (x10)
Load Average: 3.45, 2.84, 2.62
---------------------------------------------------------
Benchmark               Time             CPU   Iterations
---------------------------------------------------------
BM_Matmul/64        0.112 ms        0.112 ms         6243
BM_Matmul/128        1.02 ms         1.01 ms          689
BM_Matmul/256        11.1 ms         11.1 ms           64
BM_Matmul/512         101 ms          100 ms            7
BM_Matmul/1024        905 ms          904 ms            1
