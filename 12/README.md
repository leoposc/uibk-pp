# Assignment 12

The goal of this assignment is to study program optimizations of scalar architectures.

## Exercise 1 (1.5 Points)

### Description

Assume that during testing of your program on a scalar architecture, you found that the execution time is too high, and you have to optimize it. You suppose that the following extracts significantly impact the execution time of your program.

**a)** `c1` is of type `unsigned`:

```C
unsigned c2 = 32 * c1;

-> unsigned c2 = c1 << 5;
```

**b)** `c1` is of type `unsigned`:

```C
unsigned c2 = 15 * c1;

-> unsigned c2 = (c1 << 4) - c1;
-> unsigned c2 = (c1 << 3) + (c1 << 2) + (c1 << 1) + c1
```

**c)** `c1` is of type `unsigned`:

```C
unsigned c2 = 96 * c1;

-> unsigned c2 = (c1 << 5) + (c2 << 6)
```

_Hint_: use shift(s) and addition(s) to replace the multiplication

**d)** `c1` is of type `unsigned`:

```C
unsigned c2 = 0.125 * c1;

-> unsigned c2 = c1 >> 3
```

**e)** `a` is of type `unsigned *`:

```C
unsigned sum_fifth = 0;

for (int i = 0; i < N / 5; ++i) {
    sum_fifth += a[5 * i];
}

->  for (int i = 0; i < N / 5; ++i) {
        sum_fifth += a[(4 << i) + i];
    }
```

**f)** `a` is of type `double *`:

```C
for (int i = 0; i < N; ++i) {
    a[i] += i / 5.3;
}

// Use the fraction 3 / 16 as approximation (~0,1875; since 1 / 5.3 ~ 0.18867924)
->  for (int i = 0; i < N; ++i) {
        a[i] += ((i<<1) + 1) >> 4;
    }
```

**g)** `c1` is of type `float`:

```C
float c2 = -1 * c1;

->  uint32_t bits = *(uint32_t *)&c1;
    bits ^= 0x80000000;
    c2 = *(float *)&bits;
```

_Hint_: Inquire how IEEE 754 single-precision floating-point numbers are represented in memory.

### Tasks

1) Apply strength reduction.
2) State under which circumstances the transformation should be applied (e.g. if the cost of performing two additions is less than one multiplication).

    **a)** apply everytime
    
    **b)** apply if shift plus substraction costs less than multiplication
    
    **c)** apply if 2 shifts plus addition costs less than multiplication

    **d)** apply everytime

    **e)** apply if shift plus addition costs less than multiplication

    **f)** apply if 2 shifts plus addition costs less than division

    **g)** apply if two type casts and one XOR operation costs less than multiplication

3) After you have applied strength reduction, compare the assembly code of the original snippets with your transformation. Investigate how the compiler (`gcc`) optimizes the snippets when using `-O3` and whether the compiler uses your transformation or applies another optimization on top of it. You can use [Compiler Explorer](https://godbolt.org/) to carry out this task. The given examples are already available at <https://godbolt.org/z/NxEBrD>. Note that you can easily navigate to the assembler code for a given input source line by right-clicking, but be aware that the source for one line might be distributed among interleaved instructions.

```C
#include <stdio.h>
#include <stdlib.h>

#define N 1000

void a(unsigned c1) {
    unsigned c2 = 32 * c1;
    printf("a): %u\n", c2);
}

void a_solution(unsigned c1) {
    // TODO: insert your transformation & output
    unsigned c2 = c1 << 5;
    printf("a): %u\n", c2);
}

void b(unsigned c1) {
    unsigned c2 = 15 * c1;
    printf("b): %u\n", c2);
}

void b_solution(unsigned c1) {
    // TODO: insert your transformation & output
    unsigned c2 = (c1<<4) - c1;
    printf("b): %u\n", c2);
}

void c(unsigned c1) {
    unsigned c2 = 96 * c1;
    printf("c): %u\n", c2);
}

void c_solution(unsigned c1) {
    // TODO: insert your transformation & output
    unsigned c2 = (c1<<5) + (c2<<6);
    printf("c): %u\n", c2);
}

void d(unsigned c1) {
    unsigned c2 = 0.125 * c1;
    printf("d): %u\n", c2);
}

void d_solution(unsigned c1) {
    // TODO: insert your transformation & output
    unsigned c2 = c1 >> 3;
    printf("d): $u\n", c2);
}

void e(unsigned *a) {
    unsigned sum_fifth = 0;
    for (int i = 0; i < N / 5; ++i) {
        sum_fifth += a[5 * i];
    }
    printf("e): %u\n", sum_fifth);
}

void e_solution(unsigned *a) {
    // TODO: insert your transformation & output
    unsigned sum_fifth = 0;
    
    for (int i = 0; i < N / 5; ++i) {
        sum_fifth += a[(4<<i)+i];
    }
    printf("e) %u\n", sum_fifth);
}


void f(double *a) {
    for (int i = 0; i < N; ++i) {
        a[i] += i / 5.3;
    }
    printf("f):");
    for (int i = 0; i < N; ++i) {
        printf("%lf, ", a[i]);
    }
}

void f_solution(double *a) {
    // TODO: insert your transformation & output
    for (int i = 0; i < N; ++i) {
        a[i] += ((i<<1)+1) >> 4;
    }
}

void g(float c1) {
    float c2 = -1 * c1;
    printf("g): %u\n", c2);
}

void g_solution(float c1) {
    // TODO: insert your transformation & output
    u_int32_t bits = *(u_int32_t *)&c1;
    bits ^= 0x80000000;
    float c2 = *(float *)&bits;
    printf("g): %u\n", c2);

}

int main(void) {
    return EXIT_SUCCESS;
}
```

```ASSEM
.LC0:
        .string "a): %u\n"
a:
        mov     esi, edi
        xor     eax, eax
        mov     edi, OFFSET FLAT:.LC0
        sal     esi, 5
        jmp     printf
a_solution:
        mov     esi, edi
        xor     eax, eax
        mov     edi, OFFSET FLAT:.LC0
        sal     esi, 5
        jmp     printf
.LC1:
        .string "b): %u\n"
b:
        mov     esi, edi
        xor     eax, eax
        sal     esi, 4
        sub     esi, edi
        mov     edi, OFFSET FLAT:.LC1
        jmp     printf
b_solution:
        mov     esi, edi
        xor     eax, eax
        sal     esi, 4
        sub     esi, edi
        mov     edi, OFFSET FLAT:.LC1
        jmp     printf
.LC2:
        .string "c): %u\n"
c:
        lea     esi, [rdi+rdi*2]
        xor     eax, eax
        mov     edi, OFFSET FLAT:.LC2
        sal     esi, 5
        jmp     printf
c_solution:
        mov     esi, edi
        xor     eax, eax
        mov     edi, OFFSET FLAT:.LC2
        sal     esi, 5
        jmp     printf
.LC4:
        .string "d): %u\n"
d:
        mov     edi, edi
        pxor    xmm0, xmm0
        xor     eax, eax
        cvtsi2sdq       xmm0, rdi
        mulsd   xmm0, QWORD PTR .LC3[rip]
        mov     edi, OFFSET FLAT:.LC4
        cvttsd2si       rsi, xmm0
        jmp     printf
.LC5:
        .string "d): $u\n"
d_solution:
        mov     esi, edi
        xor     eax, eax
        mov     edi, OFFSET FLAT:.LC5
        shr     esi, 3
        jmp     printf
.LC6:
        .string "e): %u\n"
e:
        lea     rax, [rdi+4000]
        xor     esi, esi
.L13:
        add     esi, DWORD PTR [rdi]
        add     rdi, 20
        cmp     rax, rdi
        jne     .L13
        mov     edi, OFFSET FLAT:.LC6
        xor     eax, eax
        jmp     printf
.LC7:
        .string "e) %u\n"
e_solution:
        xor     ecx, ecx
        xor     esi, esi
        mov     edx, 4
.L16:
        mov     eax, edx
        sal     eax, cl
        add     eax, ecx
        add     ecx, 1
        cdqe
        add     esi, DWORD PTR [rdi+rax*4]
        cmp     ecx, 200
        jne     .L16
        mov     edi, OFFSET FLAT:.LC7
        xor     eax, eax
        jmp     printf
.LC11:
        .string "f):"
.LC12:
        .string "%lf, "
f:
        push    rbp
        mov     rax, rdi
        lea     rbp, [rdi+8000]
        push    rbx
        mov     rbx, rdi
        sub     rsp, 8
        movdqa  xmm2, XMMWORD PTR .LC8[rip]
        movdqa  xmm4, XMMWORD PTR .LC9[rip]
        movapd  xmm3, XMMWORD PTR .LC10[rip]
.L19:
        pshufd  xmm0, xmm2, 238
        cvtdq2pd        xmm1, xmm2
        movupd  xmm6, XMMWORD PTR [rax]
        add     rax, 32
        cvtdq2pd        xmm0, xmm0
        divpd   xmm1, xmm3
        movupd  xmm5, XMMWORD PTR [rax-16]
        paddd   xmm2, xmm4
        divpd   xmm0, xmm3
        addpd   xmm1, xmm6
        movups  XMMWORD PTR [rax-32], xmm1
        addpd   xmm0, xmm5
        movups  XMMWORD PTR [rax-16], xmm0
        cmp     rax, rbp
        jne     .L19
        mov     edi, OFFSET FLAT:.LC11
        xor     eax, eax
        call    printf
.L20:
        movsd   xmm0, QWORD PTR [rbx]
        mov     edi, OFFSET FLAT:.LC12
        mov     eax, 1
        add     rbx, 8
        call    printf
        cmp     rbx, rbp
        jne     .L20
        add     rsp, 8
        pop     rbx
        pop     rbp
        ret
f_solution:
        movdqa  xmm2, XMMWORD PTR .LC8[rip]
        movdqa  xmm4, XMMWORD PTR .LC9[rip]
        lea     rax, [rdi+8000]
        movdqa  xmm3, XMMWORD PTR .LC13[rip]
.L25:
        movdqa  xmm0, xmm2
        movupd  xmm6, XMMWORD PTR [rdi]
        add     rdi, 32
        paddd   xmm2, xmm4
        pslld   xmm0, 1
        movupd  xmm5, XMMWORD PTR [rdi-16]
        paddd   xmm0, xmm3
        psrad   xmm0, 4
        pshufd  xmm1, xmm0, 238
        cvtdq2pd        xmm0, xmm0
        addpd   xmm0, xmm6
        cvtdq2pd        xmm1, xmm1
        addpd   xmm1, xmm5
        movups  XMMWORD PTR [rdi-32], xmm0
        movups  XMMWORD PTR [rdi-16], xmm1
        cmp     rax, rdi
        jne     .L25
        ret
.LC15:
        .string "g): %u\n"
g:
        xorps   xmm0, XMMWORD PTR .LC14[rip]
        mov     edi, OFFSET FLAT:.LC15
        mov     eax, 1
        cvtss2sd        xmm0, xmm0
        jmp     printf
g_solution:
        movd    eax, xmm0
        mov     edi, OFFSET FLAT:.LC15
        pxor    xmm0, xmm0
        add     eax, -2147483648
        mov     DWORD PTR [rsp-12], eax
        mov     eax, 1
        cvtss2sd        xmm0, DWORD PTR [rsp-12]
        jmp     printf
main:
        xor     eax, eax
        ret
.LC3:
        .long   0
        .long   1069547520
.LC8:
        .long   0
        .long   1
        .long   2
        .long   3
.LC9:
        .long   4
        .long   4
        .long   4
        .long   4
.LC10:
        .long   858993459
        .long   1075131187
        .long   858993459
        .long   1075131187
.LC13:
        .long   1
        .long   1
        .long   1
        .long   1
.LC14:
        .long   2147483648
        .long   0
        .long   0
        .long   0
```        

## Exercise 2 (1.5 Points)

### Description

For each loop iteration instructions such as compare and add operations have to be performed. If the number of executions is sufficiently large this can have an impact on the performance of the program. Investigate the following given code examples along with their task and, for each example, study why the transformation may or may not be beneficial. \
Furthermore, for each example, you are asked to compare the performance counters of the original and the transformed code. Therefore, you should create a small test program for each configuration, compile it with `gcc` using `-O3`, and profile it with `perf` on LCC3.
Note that if not stated otherwise, variables and array elements are of type `int`.

### Tasks

1) Apply loop unrolling. Note that you can assume that `N` is odd.

```C
for (int i = 0; i < N - 1; ++i) {
    a[i] = b[i] + b[i + 1];
}
```

2) Apply loop-invariant code motion (`a` is of type `double *`):

```C
for (int i = 0; i < N; ++i) {
    a[i] *= hypot(0.3, 0.4);
}
```

3) Apply loop unswitching:

```C
for (int i = 0; i < N; ++i) {
    if (N % 2) {
        a[i] = b[i] + 5;
    } else {
        a[i] = c[i] + 5;
    }
}
```

4) Apply loop fission/distribution. Does this transformation impact the number of cache misses?

```C
for (int i = 0; i < N; ++i) {
    sum_a += a[i];
    sum_b += b[i];
    sum_c += c[i];
}
```

5) Apply loop peeling and loop fusion/combination. Note that `N` is larger than `0`.

```C
int min = a[0];
for (int i = 1; i < N; ++i) {
    min = (a[i] < min) ? a[i] : min;
}
for (int i = 0; i < N; ++i) {
    sum += a[i];
}
```

6) Apply loop splitting:

```C
for (int i = 0; i < N; ++i) {
    if (i % 2) {
        a[i] = b[i] + 4;
    } else {
        a[i] = c[i] + 5;
    }
}
```

7) Apply loop tiling (`a`, `b`, and `c` are of type `double`). You can assume that a macro `BLOCK_SIZE`, which is defined in some boilerplate code, defines a suitable block size for tiling (e.g., `#define BLOCK_SIZE 64 / sizeof(double)`). \

```C
for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
        for (int k = 0; k < N; ++k) {
            c[i][j] = a[i][k] * b[k][j];
        }
    }
}
```

```

 Performance counter stats for './a -e cache-misses,cache-references,instructions,cycles':

              0.60 msec task-clock:u              #    0.185 CPUs utilized          
                 0      context-switches:u        #    0.000 /sec                   
                 0      cpu-migrations:u          #    0.000 /sec                   
                65      page-faults:u             #  108.286 K/sec                  
           574,485      cycles:u                  #    0.957 GHz                      (55.84%)
         1,456,276      stalled-cycles-frontend:u #  253.49% frontend cycles idle   
         1,266,145      stalled-cycles-backend:u  #  220.40% backend cycles idle    
           673,669      instructions:u            #    1.17  insn per cycle         
                                                  #    2.16  stalled cycles per insn
            83,980      branches:u                #  139.905 M/sec                  
             5,546      branch-misses:u           #    6.60% of all branches          (44.16%)

       0.003247312 seconds time elapsed

       0.000311000 seconds user
       0.000979000 seconds sys



 Performance counter stats for './a_optimized -e cache-misses,cache-references,instructions,cycles':

              0.59 msec task-clock:u              #    0.267 CPUs utilized          
                 0      context-switches:u        #    0.000 /sec                   
                 0      cpu-migrations:u          #    0.000 /sec                   
                67      page-faults:u             #  114.225 K/sec                  
           690,909      cycles:u                  #    1.178 GHz                    
         1,396,038      stalled-cycles-frontend:u #  202.06% frontend cycles idle   
         1,290,814      stalled-cycles-backend:u  #  186.83% backend cycles idle    
           668,654      instructions:u            #    0.97  insn per cycle         
                                                  #    2.09  stalled cycles per insn
            78,991      branches:u                #  134.668 M/sec                  
     <not counted>      branch-misses:u                                               (0.00%)

       0.002197408 seconds time elapsed

       0.000000000 seconds user
       0.001261000 seconds sys


Some events weren't counted. Try disabling the NMI watchdog:
	echo 0 > /proc/sys/kernel/nmi_watchdog
	perf stat ...
	echo 1 > /proc/sys/kernel/nmi_watchdog

 Performance counter stats for './b -e cache-misses,cache-references,instructions,cycles':

              0.59 msec task-clock:u              #    0.241 CPUs utilized          
                 0      context-switches:u        #    0.000 /sec                   
                 0      cpu-migrations:u          #    0.000 /sec                   
                65      page-faults:u             #  109.753 K/sec                  
           428,696      cycles:u                  #    0.724 GHz                      (37.27%)
         1,460,984      stalled-cycles-frontend:u #  340.80% frontend cycles idle   
         1,296,857      stalled-cycles-backend:u  #  302.51% backend cycles idle    
           556,390      instructions:u            #    1.30  insn per cycle         
                                                  #    2.63  stalled cycles per insn
            84,538      branches:u                #  142.743 M/sec                  
             5,080      branch-misses:u           #    6.01% of all branches          (62.73%)

       0.002454617 seconds time elapsed

       0.000167000 seconds user
       0.001110000 seconds sys



 Performance counter stats for './b_optimized -e cache-misses,cache-references,instructions,cycles':

              0.58 msec task-clock:u              #    0.242 CPUs utilized          
                 0      context-switches:u        #    0.000 /sec                   
                 0      cpu-migrations:u          #    0.000 /sec                   
                67      page-faults:u             #  116.341 K/sec                  
           681,691      cycles:u                  #    1.184 GHz                    
         1,445,876      stalled-cycles-frontend:u #  212.10% frontend cycles idle   
         1,235,585      stalled-cycles-backend:u  #  181.25% backend cycles idle    
           546,435      instructions:u            #    0.80  insn per cycle         
                                                  #    2.65  stalled cycles per insn
            84,548      branches:u                #  146.811 M/sec                  
     <not counted>      branch-misses:u                                               (0.00%)

       0.002380459 seconds time elapsed

       0.000000000 seconds user
       0.001273000 seconds sys


Some events weren't counted. Try disabling the NMI watchdog:
	echo 0 > /proc/sys/kernel/nmi_watchdog
	perf stat ...
	echo 1 > /proc/sys/kernel/nmi_watchdog

 Performance counter stats for './c -e cache-misses,cache-references,instructions,cycles':

              0.63 msec task-clock:u              #    0.281 CPUs utilized          
                 0      context-switches:u        #    0.000 /sec                   
                 0      cpu-migrations:u          #    0.000 /sec                   
                73      page-faults:u             #  115.652 K/sec                  
                 0      cycles:u                  #    0.000 GHz                      (5.32%)
         1,531,379      stalled-cycles-frontend:u                                   
         1,312,188      stalled-cycles-backend:u  #    0.00% backend cycles idle    
           683,643      instructions:u                                              
                                                  #    2.24  stalled cycles per insn
            83,989      branches:u                #  133.062 M/sec                  
             4,810      branch-misses:u           #    5.73% of all branches          (94.68%)

       0.002249030 seconds time elapsed

       0.000000000 seconds user
       0.001264000 seconds sys



 Performance counter stats for './c_optimized -e cache-misses,cache-references,instructions,cycles':

              0.67 msec task-clock:u              #    0.282 CPUs utilized          
                 0      context-switches:u        #    0.000 /sec                   
                 0      cpu-migrations:u          #    0.000 /sec                   
                74      page-faults:u             #  110.206 K/sec                  
           663,113      cycles:u                  #    0.988 GHz                      (49.86%)
         1,626,258      stalled-cycles-frontend:u #  245.25% frontend cycles idle   
         1,463,616      stalled-cycles-backend:u  #  220.72% backend cycles idle    
           773,696      instructions:u            #    1.17  insn per cycle         
                                                  #    2.10  stalled cycles per insn
            83,999      branches:u                #  125.098 M/sec                  
             4,879      branch-misses:u           #    5.81% of all branches          (50.14%)

       0.002381025 seconds time elapsed

       0.000308000 seconds user
       0.001058000 seconds sys

````


## General Notes

All the material required by the tasks above (e.g., code, figures, text, etc...) must be part of the solution that is handed in. Your experiments should be reproducible and comparable to your measurements using the solution materials that you hand in.

**Every** member of your group must be able to explain the given problem, your solution, and possible findings. You may also need to answer detailed questions about any of these aspects.
