## Exercise 2 (1.5 Points)

### Description

This exercise deals with the OpenMP flush directive and why it can be necessary.

### Tasks

1. Examine [ex2/ex2.c](ex2/ex2.c) and explain what the code does from an abstract, high-level perspective. What should happen here?

   1. Initialization: It declares two integer variables data and flag. flag is set to 0 initially.
   2. Parallel Region: The code enters a parallel region defined by #pragma omp parallel num_threads(2). This means that the following block of code will be executed in parallel with two threads.
   3. Thread 0 Execution: Inside the parallel region, the code checks if the current thread's ID is 0 (omp_get_thread_num() == 0). If so, it assigns the value 42 to the variable data and sets flag to 1.
   4. Thread 1 Execution: If the current thread's ID is not 0, it must be 1 (omp_get_thread_num() == 1). In this case, it enters a loop where it continuously checks the value of flag until it becomes 1. Once flag becomes 1, it prints the values of flag and data twice.
   5. Synchronization: The intention behind this code is that Thread 1 should wait until Thread 0 sets flag to 1. Once Thread 1 observes this change, it prints the values of flag and data.

2. Compile this code with optimization level `-O3`. Run it in an interactive job (e.g. using `salloc --exclusive --tasks-per-node=1 --cpus-per-task=1 srun --pty bash`) in a loop many times (e.g. write a loop in bash that executes it 1000 times). Run this loop repeatedly. What can you observe? **Note: Please quit your interactive job once you are done!**

   After running the program with the following loop: for i in {1..1000}; do ./ex2; done. In the interactive job i saw that the program sometimes locks itself.
   That's probably, because of the race condition in the code. Since flag is not declared as with a synchronization mechanism like a flush directive, the compiler may optimize the code in a way that the second thread never sees the updated value of flag. This can lead to an infinite loop in Thread 1, as it continuously reads the old value of flag.

3. Does this code require any `#pragma omp flush` and/or `#pragma omp atomic` directives? If it does, where are they necessary? If it does not, why not?

   The flush directive ensures that the updates made by one thread to shared variables are visible to other threads. Specifically, you can use flush to ensure that the update to the flag variable made by Thread 0 is visible to Thread 1.
   Flush directives commented in ex2_flush.c.

   The use of OpenMP's atomic directive isn't necessary because there's no concurrent write access(from multiple threads) to shared variables.
