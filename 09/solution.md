### Seling Tobias

# Assignment 9

The goal of this assignment is to study several means of vectorizing a simple program.

## Exercise 1 (1 Point)

### Description

In this exercise, we will employ auto-vectorization of the compiler to increase the performance of a small program that computes a multiply-add operation on three vectors.

### Tasks

- Write a sequential program that computes `a[i] += b[i] * c[i]` for three `float` vectors `a`, `b`, and `c`. Enclose this computation in a loop such that it is repeated `1e6` times. I.e. your code should look like this:

```
for(int run = 0; run < repetitions; ++run) {
    for(int i = 0; i < size; ++i) {
        a[i] += b[i] * c[i];
    }
}
```

- Initialize the vectors with constant values and add some output that allows you to verify correct computation of the program for subsequent optimization steps (try to avoid overflows). Compile this program on LCC3 with `gcc 12.2.0` using `-O1` and measure the execution time **of the computation only** for several problem sizes (=vector lengths). This sequential program is our baseline reference.
- Try to use auto-vectorization in the compiler to vectorize the computation. Investigate which flag(s) to use for that, and try to limit your compiler change to only enable vectorization but not any other optimizations. Measure the execution time for the same problem sizes as before and compute the respective speedups. What can you observe in terms of performance? Is the result still correct? Does varying the problem size affect the performance gain or loss?
- Use `perf` to further investigate the origin of any performance difference you might observe. `perf stat -e rYYXX` (mind the order of X and Y!) allows you to measure custom events supported by the CPU, where - on Intel systems - XX is the so-called _event code_ and YY is the so-called _unit mask_ (also called _umask_). A few event codes and unit masks for measuring vectorized instructions are given below. Check which ones are suitable for your investigation:

| Name                                 | Event Code | Unit Mask | result seq (size 2048) | result vectorized (size 2048) | Description                                                                                                              |
| ------------------------------------ | :--------: | :-------: | :--------------------: | :---------------------------: | ------------------------------------------------------------------------------------------------------------------------ |
| FP_COMP_OPS_EXE.X87                  |     10     |    01     |           0            |               0               | Counts the number of floating-point computational operations executed using the x87 FPU instructions.                    |
| FP_COMP_OPS_EXE.MMX                  |     10     |    02     |           0            |               0               | Counts the number of MMX (MultiMedia eXtension) instructions executed.                                                   |
| FP_COMP_OPS_EXE.SSE_FP               |     10     |    04     |           0            |               0               | Counts the number of SSE (Streaming SIMD Extensions) floating-point computational operations executed.                   |
| FP_COMP_OPS_EXE.SSE2_INTEGER         |     10     |    08     |         34,052         |             9,208             | Counts the number of integer computational operations executed using SSE2 instructions.                                  |
| FP_COMP_OPS_EXE.SSE_FP_PACKED        |     10     |    10     |           0            |         1,024,007,735         | Counts the number of packed floating-point computational operations executed using SSE instructions.                     |
| FP_COMP_OPS_EXE.SSE_FP_SCALAR        |     10     |    20     |           0            |               0               | Counts the number of scalar floating-point computational operations executed using SSE instructions.                     |
| FP_COMP_OPS_EXE.SSE_SINGLE_PRECISION |     10     |    40     |           0            |               0               | Counts the number of single-precision (32-bit) floating-point computational operations executed using SSE instructions.  |
| FP_COMP_OPS_EXE.SSE_DOUBLE_PRECISION |     10     |    80     |           0            |               0               | Counts the number of double-precision (64-bit) floating-point computational operations executed using SSE2 instructions. |

<sub>In case you are interested: For further events relevant to the CPU type on LCC3 and short event descriptions, see [Intel's perfmon web interface](https://perfmon-events.intel.com/) (pay attention to choosing a suitable micro-architecture) or alternatively [Intel® 64 and IA-32 Architectures Software Developer’s Manual Volume 3B: System Programming Guide, Part 2](https://www.intel.com/content/www/us/en/architecture-and-technology/64-ia-32-architectures-software-developer-vol-3b-part-2-manual.html). It lists all events that can be counted with `perf` on our hardware.</sub>

- Enter the wall clock time of the sequential program and the auto-vectorized version with size 2048 and 1e6 repetitions to the spreadsheet linked on Discord.

## Exercise 2 (1 Point)

### Description

Instead of relying on the compiler to vectorize the code for us, we will do so manually in this exercise, using OpenMP.

### Tasks

- Vectorize your sequential program using OpenMP. Do not use any OpenMP thread-based parallelism.
- Compile your OpenMP-vectorized code with `-O1` but without any compiler flags for auto-vectorization and compare its performance for the problem size 2048 to both the sequential version and the compiler-vectorized version. What can you observe? Is the result still correct?
  As depicted in figure_2 the computation still works and it is faster than the auto-vectorized version of the compiler.
- Verify any findings using `perf` as described in Exercise 1.

Here is the updated table:
| Name | Event Code | Unit Mask | result seq (size 2048) | result omp vectorized (size 2048) | result omp vectorized double (size 2048) |
|--------------------------------------|:----------:|:---------:|:----------------------:|:---------------------------------:|:----------------------------------------:|
| FP_COMP_OPS_EXE.X87 | 10 | 01 | 0 | 0 | 0 |
| FP_COMP_OPS_EXE.MMX | 10 | 02 | 0 | 0 | 0 |
| FP_COMP_OPS_EXE.SSE_FP | 10 | 04 | 0 | 0 | 0 |
| FP_COMP_OPS_EXE.SSE2_INTEGER | 10 | 08 | 34,052 | 9,135 | 35,443 |
| FP_COMP_OPS_EXE.SSE_FP_PACKED | 10 | 10 | 0 | 1,024,015,454 | 2,057,498,531 |
| FP_COMP_OPS_EXE.SSE_FP_SCALAR | 10 | 20 | 0 | 0 | 0 |
| FP_COMP_OPS_EXE.SSE_SINGLE_PRECISION | 10 | 40 | 0 | 0 | 0 |
| FP_COMP_OPS_EXE.SSE_DOUBLE_PRECISION | 10 | 80 | 0 | 0 | 0 |

- Repeat the sequential and OpenMP executions when changing the data type from `float` to `double`. What can you observe?

The double version is slower than the float omp version, but it has also almost the same execution speed as the auto-vectoized version, to the point, where you only see one of them on the graph since they overlap.

- How does the solution for this Exercise compare to Exercise 1? Are there any advantages or disadvantages?

The advantage is the faster execution speed. Disadvantage may be the additional header file and additional lines of code (which is kind of negligable)

- Enter the wall clock time of the OpenMP-vectorized version with size 2048, 1e6 repetitions and data type `float` to the spreadsheet linked on Discord.

## Exercise 3 (1 Point)

### Description

Instead of relying on OpenMP for vectorization, we will do so using compiler-specific intrinsics in this exercise.

### Tasks

- Vectorize your code for `float` types using the gcc-specific intrinsic functions `_mm_load_ps`, `_mm_add_ps`, `_mm_mul_ps`, and `_mm_store_ps`. Do not forget to include the respective header `xmmintrin.h`.
- Compile your manually vectorized code with `-O1` but without any compiler flags for auto-vectorization and compare its performance for your set of problem sizes to your previous code versions. What can you observe? Is the result still correct?

Finding depicted in figure_3.

- Verify any findings using `perf` as described in Exercise 1.

| Name                                 | Event Code | Unit Mask | result seq (size 2048) | result intrinsic |
| ------------------------------------ | :--------: | :-------: | :--------------------: | :--------------: |
| FP_COMP_OPS_EXE.X87                  |     10     |    01     |           0            |        0         |
| FP_COMP_OPS_EXE.MMX                  |     10     |    02     |           0            |        0         |
| FP_COMP_OPS_EXE.SSE_FP               |     10     |    04     |           0            |        0         |
| FP_COMP_OPS_EXE.SSE2_INTEGER         |     10     |    08     |         34,052         |      9,979       |
| FP_COMP_OPS_EXE.SSE_FP_PACKED        |     10     |    10     |           0            |  1,024,006,568   |
| FP_COMP_OPS_EXE.SSE_FP_SCALAR        |     10     |    20     |           0            |        0         |
| FP_COMP_OPS_EXE.SSE_SINGLE_PRECISION |     10     |    40     |           0            |        0         |
| FP_COMP_OPS_EXE.SSE_DOUBLE_PRECISION |     10     |    80     |           0            |        0         |

- How does the solution for this Exercise compare to Exercise 2 and Exercise 1? Are there any advantages or disadvantages?
- Enter the wall clock time of the compiler-specific intrinsics version with size 2048 and 1e6 repetitions to the spreadsheet linked on Discord.
