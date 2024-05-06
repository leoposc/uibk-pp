# Assignment 7

## Exercise 1

```C
a[0] = 0;
#pragma omp parallel for
for (i=1; i<N; i++) {
    a[i] = 2.0*i*(i-1);
    b[i] = a[i] - a[i-1];
}
```

dependence: True depencence, loop carried dependence.

### Solution:

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

---

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

race conditon: The nowait clause in the first loop might allow the threads to start executing the second loop before the
first one finishes, causing data races.

### Solution:

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

---

```C
#pragma omp parallel for
for (i=1; i<N; i++) {
    x = sqrt(b[i]) - 1;
    a[i] = x*x + 2*x + 1;
}
```

if x is defined public, there is a race conditon

### solution:

```C
#pragma omp parallel for private(x)
for (i=1; i<N; i++) {
    x = sqrt(b[i]) - 1;
    a[i] = x*x + 2*x + 1;
}
```

---

```C
f = 2;
#pragma omp parallel for private(f,x)
for (i=1; i<N; i++) {
    x = f * b[i];
    a[i] = x - 7;
}
a[0] = x; 
```

correct

---

```C
sum = 0; 
#pragma omp parallel for
for (i=1; i<N; i++) {
    sum = sum + b[i];
}
```

race condtion on sum

### solution

```C
sum = 0; 
#pragma omp parallel for reduction(+: sum)
for (i=1; i<N; i++) {
    sum = sum + b[i];
}
```

## Exercise 2

### Dependence Analysis:

In some cases, the analysis identifies "bad data dependence" or a "missed" dependency, which suggests that vectorization
might not be possible due to data dependencies.

### successful or unsuccessful vectorization:

Indicates when a loop is successfully vectorized and when it fails to vectorize.

### beyond checking for dependencies and semantic correctness

scalar cycle detection, vectorization factor determination, data reference alignment analysis, and profitability
estimation

### Specific Findings:

1) analysis.c:27, vectorization failed due to function calls or unanalyzable data references (printf function call).
2) analysis.c:22, vectorization failed due to non-affine evolution of offsets and bad data dependencies.
3) analysis.c:10, vectorization succeeded with a vectorization factor of 4, indicating that the loop iterations can be
   efficiently parallelized.

## Exercise 3:

### 1.

Yes this code can be parallized manually. Yes a compiler should be able to parallize, because of the simplicity of this
loop.

### 2.

```C
for (int i=0; i<=(N-4) / 9; i++) {
    A[4 + 9i] = 0;
}
```

### 3.

Yes it does have a true dependence on itself. Distance vector: (1, 0, -1)
Directon vector: (<, = , >)