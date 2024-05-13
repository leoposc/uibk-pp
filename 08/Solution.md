#### Team 3: Göthert Philipp Robert, Schmid Leopold Julius, Seling Tobias

# Assignment 8

## Exercise 1

### Description

This exercise consists of exploring the effects of OpenMP thread affinity.

### Tasks

1. Write an OpenMP program that atomically increments an `int` using `#pragma omp atomic` in a parallel for loop for a large number of iterations, i.e. such that the program takes at least 2 seconds to execute. Have the program print the time required to process the entire loop. Compile your program with gcc 12.2.0 and optimization level `-O3`. Do not perform any manual optimizations such as reducing the number of atomic operations.
2. Run your program with 6 threads. Explore the affinity features of OpenMP 4.0 to change the way threads are mapped to cores, e.g. using a single CPU only or using both CPUs. Explain the affinity settings that you chose.
   These are the settings of OMP_PROC_BIND:

- Close Affinity: Threads are bound to adjacent or nearby CPU cores to improve cache locality.

- Spread Affinity: Threads are spread across different CPU cores to maximize system throughput.

- Master Affinity: Only the master thread is initially bound to a CPU core, allowing other threads to float across cores.

You can also specify for OMP_PLACES how places(HW resource that can execute an OpenMP thread) are defined:

- threads: every HW thread defines a place
- cores: every core defines a place
- socket: every socket defines a place

### The results of testing each combination:

Running with affinity settings: OMP_PROC_BIND=close OMP_PLACES=sockets
Time taken: 15.092194 seconds

Running with affinity settings: OMP_PROC_BIND=close OMP_PLACES=cores
Time taken: 9.213874 seconds

Running with affinity settings: OMP_PROC_BIND=close OMP_PLACES=threads
Time taken: 8.037649 seconds

Running with affinity settings: OMP_PROC_BIND=spread OMP_PLACES=sockets
Time taken: 15.959491 seconds

Running with affinity settings: OMP_PROC_BIND=spread OMP_PLACES=cores
Time taken: 17.469906 seconds

Running with affinity settings: OMP_PROC_BIND=spread OMP_PLACES=threads
Time taken: 15.785966 seconds

Running with affinity settings: OMP_PROC_BIND=master OMP_PLACES=sockets
Time taken: 9.173151 seconds

Running with affinity settings: OMP_PROC_BIND=master OMP_PLACES=cores
Time taken: 3.481315 seconds

Running with affinity settings: OMP_PROC_BIND=master OMP_PLACES=threads
Time taken: 3.131548 seconds

### The best result:

Running with affinity settings: OMP_PROC_BIND=master OMP_PLACES=threads
Time taken: 3.131548 seconds

3. Benchmark your program with these affinity settings. What can you observe?
4. Enter the time for N=500.000.000 into the comparison spreadsheet linked on Discord.

## Exercise 2 (1.5 Points)

### Description

This exercise consists of extending the Hadamard product implementation of the previous assignment.

### Tasks

1. Implement a parallel version of the Hadamard product using OpenMP. Use the snippet below as sequential implementation.

   ```c
   for (size_t i = 0; i < n; ++i) {
       for (size_t j = 0; j < n; ++j) {
           c[i][j] = a[i][j] * b[i][j];
       }
   }
   ```

2. Benchmark your serial implementations and your parallel implementations with 1, 2, 4, 6 and 12 threads on LCC3 using N=10.000², 20.000² and 30.000². Use OpenMP's time measurement function to measure only the computational loop.
3. Use the 3 loop scheduling methods discussed in the lecture, `static`, `dynamic` and `guided`. Explain their differences and compare their performance for the two code snippets. What can you observe?

### Static Scheduling:

- In static scheduling, iterations of the loop are divided into chunks of approximately equal size at compile-time or runtime.
- Each thread is assigned a contiguous chunk of iterations to execute.
- The chunk size can be specified explicitly using the chunk clause in the schedule directive, or it can be left to the implementation to determine.
- Static scheduling is useful when the workload of each iteration is roughly the same, and there's little variability in execution time across iterations.
- It offers good load balancing when the iterations have a uniform workload.

### Dynamic Scheduling:

- In dynamic scheduling, iterations are divided into chunks, and threads are dynamically assigned these chunks at runtime.
- Each thread executes a chunk of iterations and requests another chunk upon completion until all iterations are processed.
- The chunk size can be specified explicitly using the chunk clause in the schedule directive.
- Dynamic scheduling is beneficial when the workload of iterations varies significantly, and load balancing is essential.
- It incurs overhead due to dynamic allocation of chunks and thread synchronization.

### Guided Scheduling:

- Guided scheduling is similar to dynamic scheduling, but the chunk size decreases over time.
- Initially, larger chunks are assigned to threads, and as the number of iterations decreases, smaller chunks are assigned.
- This approach helps in improving load balancing, especially in scenarios where the workload of iterations varies widely.
- Guided scheduling is particularly useful when there's a large variation in the execution time of iterations, and dynamic scheduling alone might result in load imbalance.
- It provides better load balancing compared to dynamic scheduling but might have higher overhead due to frequent adjustments of chunk sizes.

4. In addition, try the loop scheduling methods `auto` and `runtime`. What do they do, what can you observe?

### Auto Scheduling:

The auto scheduling policy delegates the choice of the scheduling method to the OpenMP implementation.

### Runtime Scheduling:

With runtime scheduling, the scheduling method is determined at runtime based on the value of the OMP_SCHEDULE environment variable.

5. Enter the time for N=65.536² into the comparison spreadsheet linked on Discord.

## General Notes

All the material required by the tasks above (e.g., code, figures, text, etc...) must be part of the solution that is handed in. Your experiments should be reproducible and comparable to your measurements using the solution materials that you hand in.

**Every** member of your group must be able to explain the given problem, your solution, and possible findings. You may also need to answer detailed questions about any of these aspects.
