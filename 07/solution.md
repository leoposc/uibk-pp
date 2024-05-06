#### Team 3: Göthert Philipp Robert, Schmid Leopold Julius, Seling Tobias

# Solution: Assignment 7

The goal of this assignment is to work with data and control dependencies.

## Exercise 1 (1 Point)

### Description

Consider the following, individual code examples in the context of dependence analysis, race conditions, and parallelization:

### Snippet 1

```C
a[0] = 0;
#pragma omp parallel for
for (i=1; i<N; i++) {
    a[i] = 2.0*i*(i-1);
    b[i] = a[i] - a[i-1];
}
```

In this code snippet there is a true dependence, since the a[i] is written in the 1. and
both a[i] and a[i-1] are accessed in the 2. line.

### Solution

```C
a[0] = 0;
#pragma omp parallel for
for (i=1; i<N; i++) {
    a[i] = 2.0*i*(i-1);
}
#pragma omp parallel for
for (i=1; i<N; i++) {
    b[i] = a[i] - a[i-1];
}
```

### Snippet 2

```C
a[0] = 0;
#pragma omp parallel
{
    #pragma omp for nowait
    for (i=1; i<N; i++) {
        a[i] = 3.0*i*(i+1);
    }
    #pragma omp for
    for (i=1; i<N; i++) {
        b[i] = a[i] - a[i-1];
    }
}
```

The problem arises because the computation of b[i] depends on the values of a[i] and a[i-1], and these values might be modified by different threads concurrently, because of the nowait. This creates a race condition, where the result of the computation depends on the order in which threads execute their iterations.

### Solution

```C
a[0] = 0;
#pragma omp parallel
{
    #pragma omp for
    for (i=1; i<N; i++) {
        a[i] = 3.0*i*(i+1);
    }
    #pragma omp for
    for (i=1; i<N; i++) {
        b[i] = a[i] - a[i-1];
    }
}
```

### Snippet 3

```C
#pragma omp parallel for
for (i=1; i<N; i++) {
    x = sqrt(b[i]) - 1;
    a[i] = x*x + 2*x + 1;
}
```

This snippets loop is using shared variables inside the loop without considering potential race conditions. To avoid race conditions, each thread needs its own private copy of x.

### Solution

```C
#pragma omp parallel for private(x)
for (i=1; i<N; i++) {
    x = sqrt(b[i]) - 1;
    a[i] = x*x + 2*x + 1;
}
```

### Snippet 4

```C
f = 2;
#pragma omp parallel for private(f,x)
for (i=1; i<N; i++) {
    x = f * b[i];
    a[i] = x - 7;
}
a[0] = x;
```

This snippet has no dependence or race condition. (f doesn't have to be private, but it's not an issue)

### Snippet 5

```C
sum = 0;
#pragma omp parallel for
for (i=1; i<N; i++) {
    sum = sum + b[i];
}
```

Since each thread will be updating sum concurrently, there is a race condition leading to incorrect results due to concurrent writes.

### Solution

```C
sum = 0;
#pragma omp parallel for reduction(+: sum)
for (i=1; i<N; i++) {
    sum += b[i];
}
```

### Tasks

1. For each example, investigate whether it is parallelized correctly or whether there are any dependencies, and how any potential parallelization mistakes can be solved while keeping the parallelism. Are there multiple solutions and if so, what are their advantages and disadvantages?

## Exercise 2 (1 Point)

### Description

- Compilers often perform dependence analysis as a pre-step in order to safely perform optimizations such as vectorization in a second step. In this exercise, we will look at the first step only, namely compiler capabilities and reporting.

### Tasks

1. Compile the given program [analysis.c](analysis.c) with gcc 12.2.0 (`module load  gcc/12.2.0-gcc-8.5.0-p4pe45v`) and the flags `-O2 -ftree-vectorize -fopt-info-vec-all-internals`.
2. Examine the output.

   #### What information about dependence analysis can you find in the output?

   The output provides a detailed overview of the dependence analysis process, including detected dependencies, reasons for analysis failures, and alignment considerations. It provides reasons for failures, such as "bad data dependence".

   #### Can you identify any information pointing to successful or unsuccessful vectorization?

   It checks each loop if it can successfully vectorize it using different vectorization modes.
   Breakdown of what each part of "V4SI" represents:

   V: Stands for "vector".
   4: Indicates that the vector contains 4 elements.
   SI: Represents signed integers.

   Example successful vectorization(analysis.c:10):
   Analysis succeeded with vector mode V4SI
   The result for vector mode V16QI would be the same

   Example unsuccessful vectorization(analysis.c:22):
   "Analysis failed with vector mode V4SI"
   "Re-trying analysis with vector mode V8QI"
   "Analysis failed with vector mode V8QI"
   "Re-trying analysis with vector mode V4QI"
   "Analysis failed with vector mode V4QI"
   "Couldn't vectorize loop"
   "Possible alias involving gather/scatter between a[_4] and a[i_47]"

   #### Does the compiler perform any analysis beyond checking for dependencies and semantic correctness?

   Loop Nest Analysis: Determines the loop hierarchy and relationships between nested loops.
   Vectorization Analysis: Identifies if loops can be efficiently vectorized based on loop forms, data references, scalar cycles, and iterations.
   Data Reference Analysis: Analyzes data references within loops, including their alignment and potential misalignment for vectorization.
   Scalar Cycle Analysis: Detects and analyzes scalar cycles within loops to assess vectorization potential.
   Pattern Recognition: Recognizes patterns within loop code that may impact vectorization decisions.
   Data Dependence Analysis: Checks for dependencies between data references to ensure correct execution order and avoid hazards.
   Loop Operation Analysis: Analyzes loop operations, such as phis, to understand their impact on vectorization.
   Cost Model Analysis: Estimates the cost of vectorization compared to scalar execution, considering loop overhead, iteration costs, and vectorization overhead.

## Exercise 3 (1 Point)

### Description

Investigate the following given code examples along with their task.

### Tasks

1. Investigate the given code excerpt. Can this code be safely parallelized manually? Can this code be safely parallelized by the compiler?
   ```C
   void copy(double* x, double* y) {
       for(int i = 0; i < 1024; i++) {
           x[i] = y[i];
       }
   }
   ```

### Solution

Yes, this code can be safely parallelized both manually and by the compiler.
Manual Parallelization:

```C
void copy(double* x, double* y) {
    #pragma omp parallel for
    for(int i = 0; i < 1024; i++) {
        x[i] = y[i];
    }
}
```

Compiler Parallelization:
Compiler flags like -floop-parallelize-all can enable automatic parallelization. When enabled, the compiler will analyze the loop and, if deemed profitable, parallelize it. When automatic parallelization is enabled, the compiler will attempt to parallelize the loop internally without requiring any changes to the source code. However, the effectiveness of compiler parallelization can vary depending on the compiler and optimization settings.

2. Normalize the following loop nest:
   ```C
   for (int i=4; i<=N; i+=9) {
       for (int j=0; j<=N; j+=5) {
           A[i] = 0;
       }
   }
   ```

### Solution

The inner loop can be discarded, since j isn't accessed inside the loop.
Algorithm:
First of all, offset the loop for (i = k; i <= n; i += c), such that i will start from 0: for (i = 0; i <= n - k; i += c), and for each read occurrence of i inside the loop do i:=i+k. (you can't optimize in that method if i is written inside the loop)

Handling the jumping gaps. currently, i is incremented by c each iteration, so we have to divide by c in order to increment in 1: for (i = 0; i <= (n - k)/c; i += 1), and for each read occurrence of i inside the loop do i:=i\*c.

```C
for (int i=0; i<=(N-4)/9; i+=1) {
     A[4+i*9] = 0;
}
```

3. Does the following code excerpt hold any dependencies? If not, how would you parallelize it? If yes, what are the distance and direction vectors?
   ```C
   for(int i = 1; i < N; i++) {
       for(int j = 1; j < M; j++) {
           for(int k = 1; k < L; k++) {
               a[i+1][j][k-1] = a[i][j][k] + 5;
           }
       }
   }
   ```

### Solution

Yes, the code snippet contains a true dependence on itself. Specifically, due to the assignment statement a[i+1][j][k-1] = a[i][j][k] + 5;. The dependency arises because the value of a[i+1][j][k-1] in one iteration depends on the value of a[i][j][k] computed in a previous iteration.
The distance vectors represent the differences in loop indices between the source and destination of the data dependency. In this case, the distance vectors are(1, 0, -1)
The direction vectors indicate the direction in which the data dependency flows. In this case, the direction vector is (<, =, >).

## General Notes

All the material required by the tasks above (e.g., code, figures, text, etc...) must be part of the solution that is handed in. Your experiments should be reproducible and comparable to your measurements using the solution materials that you hand in.

**Every** member of your group must be able to explain the given problem, your solution, and possible findings. You may also need to answer detailed questions about any of these aspects.
