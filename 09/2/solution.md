### What can you observe? Is the result still correct?

The OpenMP-vectorized code and the compiler-optimized code perform similarly, both significantly faster than the sequential version.\
The output is still correct. \
The OpenMP vectorization aligns well with the compiler's auto-vectorization capabilities, providing similar performance benefits. So manual vectorization using OpenMP can be as effective as relying on the compiler's optimizations when properly utilized.

### Repeat the sequential and OpenMP executions when changing the data type from float to double. What can you observe?
Sequential Execution (not vectorized): The times for sequential execution are similar for both data types, indicating the base computational complexity is comparable regardless of the data type.
OpenMP Execution: The OpenMP-accelerated execution for doubles is slower (1.566916 seconds) compared to floats (0.511293 seconds). This is expected due to the larger size and higher precision of double-precision floating-point numbers, which require more processing power and memory bandwidth.

### How does the solution for this Exercise compare to Exercise 1? Are there any advantages or disadvantages?
No real differences. 
One advantage of openmp could be, that you have control over what´s getting vectorized.