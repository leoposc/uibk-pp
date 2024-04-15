# Assignment 4

The goal of this assignment is to get to know the basic functionality of OpenMP.

## Exercise 1 (1.5 Points)

### Description

This exercise consists of implementing a Monte Carlo Pi approximation in OpenMP.

### Tasks

1) Review the pthreads-based implementation provided in [monte_carlo_pi/mc_pi_pthreads.c](monte_carlo_pi/mc_pi_pthreads.c). Benchmark it with 1, 2, 4, 6, and 12 threads on LCC3. What can you observe?
2) Implement parallel versions of this approximation using OpenMP. In total, three different versions using the following OpenMP constructs should be provided:
    1) `critical` section
    2) `atomic` statement
    3) `reduction` clause
3) To increase the performance difference among these versions, make sure you increment the samples counter directly, without aggregating to private variables first.
4) Benchmark your OpenMP implementations with the same number of threads using OpenMP's time measurement function. What can you observe? How do those results compare to your earlier measurements?

    Benchmarking mc_pi_atomic with 1 threads...
    Approximation of PI took 11.254 seconds with 1 threads - value: 3.1415790800
    ----------------------------------------------
    Benchmarking mc_pi_atomic with 2 threads...
    Approximation of PI took 13.401 seconds with 2 threads - value: 3.1415909829
    ----------------------------------------------
    Benchmarking mc_pi_atomic with 4 threads...
    Approximation of PI took 35.818 seconds with 4 threads - value: 3.1415605314
    ----------------------------------------------
    Benchmarking mc_pi_atomic with 6 threads...
    Approximation of PI took 24.088 seconds with 6 threads - value: 3.1415958800
    Benchmarking mc_pi_atomic with 12 threads...
    Approximation of PI took 21.931 seconds with 12 threads - value: 3.1415694114
    ----------------------------------------------
    Benchmarking mc_pi_critical with 1 threads...
    Approximation of PI took 14.125 seconds with 1 threads - value: 3.1415790800
    ----------------------------------------------
    Benchmarking mc_pi_critical with 2 threads...
    Approximation of PI took 53.031 seconds with 2 threads - value: 3.1415909829
    ----------------------------------------------
    Benchmarking mc_pi_critical with 12 threads...
    Approximation of PI took 169.081 seconds with 12 threads - value: 3.1415694114
    ----------------------------------------------
    Benchmarking mc_pi_reduction with 1 threads...
    Approximation of PI took 8.495 seconds with 1 threads - value: 3.1415790800
    ----------------------------------------------
    Benchmarking mc_pi_reduction with 2 threads...
    Approximation of PI took 4.290 seconds with 2 threads - value: 3.1415909829
    ----------------------------------------------
    Benchmarking mc_pi_reduction with 4 threads...
    Approximation of PI took 2.140 seconds with 4 threads - value: 3.1415605314
    ----------------------------------------------
    Benchmarking mc_pi_reduction with 6 threads...
    Approximation of PI took 1.477 seconds with 6 threads - value: 3.1415958800
    ----------------------------------------------
    Benchmarking mc_pi_reduction with 12 threads...
    Approximation of PI took 0.803 seconds with 12 threads - value: 3.1415694114
    ----------------------------------------------
    Benchmarking mc_pi_pthreads with 1 threads...
    Approximation of PI took 10.857 seconds with 1 threads - value: 3.1415790800
    ----------------------------------------------
    Benchmarking mc_pi_pthreads with 2 threads...
    Approximation of PI took 5.460 seconds with 2 threads - value: 3.1415909829
    ----------------------------------------------
    Benchmarking mc_pi_pthreads with 4 threads...
    Approximation of PI took 2.752 seconds with 4 threads - value: 3.1415605314
    ----------------------------------------------
    Benchmarking mc_pi_pthreads with 6 threads...
    Approximation of PI took 1.973 seconds with 6 threads - value: 3.1415958743
    ----------------------------------------------
    Benchmarking mc_pi_pthreads with 12 threads...
    Approximation of PI took 0.953 seconds with 12 threads - value: 3.1415694114
    ----------------------------------------------

5) The tool `/usr/bin/time` can be used to get useful information on the properties of a program's execution, e.g. its execution time or the maximum amount of main memory used. Measure the execution time of your OpenMP implementation using `/usr/bin/time -v <program_name>`. Take a look at the output, specifically "user time" and "elapsed (wall clock) time". How do they differ? Does either of them match the time measurement function of OpenMP?
6) Add the wall clock time measurements for 12 threads on LCC3 to the comparison spreadsheet linked on Discord.

## Exercise 2 (1.5 Points)

### Description

In this exercise, you are asked to investigate the effect of false sharing in multi-threaded programs.

### Tasks

1) Implement (or copy from Exercise 1) a parallel Monte Carlo PI version that uses a local sum approach, i.e. that first aggregates to a per-thread private variable before using `atomic` to aggregate the entire sum of samples.
2) Create a second version that does not rely on private variables but a single array where each thread gets one element for local sum storage. In memory, the data layout should then look like `[thread_0][thread_1][_thread_2][...]`.
3) Create a third version that continues to use a single array but add padding to it, ensuring that the individual local sum storage locations are separated by unused data, e.g. `[thread_0][N_unused_bytes][thread_1][N_unused_bytes][thread_2][...]`. How you achieve this padding is up to you (there are several implementation possibilities). How large should the padding distance ideally be?
4) Benchmark all three versions (private variable, array, array with padding) and document your results. Also check the L1 cache misses using `perf stat`. Feel free to also check for this effect on your local machines and report the data (including the CPU type!).

Benchmarks ran on LCC3:

    Benchmarking exercise02_v1 with 12 threads...
    Approximation of PI took 7.135 seconds with 12 threads - value: 3.1415694114

    Performance counter stats for './exercise02_v1 12':

                1,207      LLC-load-misses:u                                           
                    68      LLC-store-misses:u                                          

        7.139038480 seconds time elapsed

        14.228610000 seconds user
        0.005964000 seconds sys


    ----------------------------------------------
    Benchmarking exercise02_v2 with 12 threads...
    Approximation of PI took 9.135 seconds with 12 threads - value: 3.1415694114

    Performance counter stats for './exercise02_v2 12':

                1,250      LLC-load-misses:u                                           
                    79      LLC-store-misses:u                                          

        9.138625357 seconds time elapsed

        18.221162000 seconds user
        0.002974000 seconds sys


    ----------------------------------------------
    Benchmarking exercise02_v3 with 12 threads...
    Approximation of PI took 8.451 seconds with 12 threads - value: 3.1415694114

    Performance counter stats for './exercise02_v3 12':

                1,271      LLC-load-misses:u                                           
                    66      LLC-store-misses:u                                          

        8.454501184 seconds time elapsed

        16.839904000 seconds user
        0.005848000 seconds sys


    ----------------------------------------------
    Benchmarking exercise02_v3_1 with 12 threads...
    Approximation of PI took 8.012 seconds with 12 threads - value: 3.1415694114

    Performance counter stats for './exercise02_v3_1 12':

                1,204      LLC-load-misses:u                                           
                    40      LLC-store-misses:u                                          

        8.015302785 seconds time elapsed

        15.965050000 seconds user
        0.002971000 seconds sys


    ----------------------------------------------

5) Enter the wall clock time of each version for 12 threads on LCC3 to the comparison spreadsheet linked on Discord.

## General Notes

All the material required by the tasks above (e.g., code, figures, text, etc...) must be part of the solution that is handed in. Your experiments should be reproducible and comparable to your measurements using the solution materials that you hand in.

**Every** member of your group must be able to explain the given problem, your solution, and possible findings. You may also need to answer detailed questions about any of these aspects.
