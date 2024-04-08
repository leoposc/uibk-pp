### Group 3: Göthert Philipp Robert, Schmid Leopold Julius, Seling Tobias	

# Assignment 2

## Exercise 1

### Improve program performance

Make usage of compiler optimazations.

### Parallelize

Divide the array in vertically sliced stripes and assign the strips to ranks.



## Exercise 2

#### Settings:
 
`Matrix size: 10.000, Cache line size: 64B`

    valgrind --tool=cachegrind ./fast 
    ==1914231== I   refs:      136,303
    ==1914231== I1  misses:        905
    ==1914231== LLi misses:        878
    ==1914231== I1  miss rate:    0.66%
    ==1914231== LLi miss rate:    0.64%
    ==1914231== 
    ==1914231== D   refs:       45,861  (33,180 rd   + 12,681 wr)
    ==1914231== D1  misses:      1,880  ( 1,318 rd   +    562 wr)
    ==1914231== LLd misses:      1,688  ( 1,148 rd   +    540 wr)
    ==1914231== D1  miss rate:     4.1% (   4.0%     +    4.4%  )
    ==1914231== LLd miss rate:     3.7% (   3.5%     +    4.3%  )
    ==1914231== 
    ==1914231== LL refs:         2,785  ( 2,223 rd   +    562 wr)
    ==1914231== LL misses:       2,566  ( 2,026 rd   +    540 wr)
    ==1914231== LL miss rate:      1.4% (   1.2%     +    4.3%  )


    valgrind --tool=cachegrind ./slow
    ==1914154== I   refs:      136,303
    ==1914154== I1  misses:        905
    ==1914154== LLi misses:        878
    ==1914154== I1  miss rate:    0.66%
    ==1914154== LLi miss rate:    0.64%
    ==1914154== 
    ==1914154== D   refs:       45,861  (33,180 rd   + 12,681 wr)
    ==1914154== D1  misses:      1,880  ( 1,318 rd   +    562 wr)
    ==1914154== LLd misses:      1,688  ( 1,148 rd   +    540 wr)
    ==1914154== D1  miss rate:     4.1% (   4.0%     +    4.4%  )
    ==1914154== LLd miss rate:     3.7% (   3.5%     +    4.3%  )
    ==1914154== 
    ==1914154== LL refs:         2,785  ( 2,223 rd   +    562 wr)
    ==1914154== LL misses:       2,566  ( 2,026 rd   +    540 wr)
    ==1914154== LL miss rate:      1.4% (   1.2%     +    4.3%  )

    While the results perf seem to be very fluctuant and therefore not really reliable and the results of the self written functions also flawed, cachegrind seems to be the only program which delivers solid results. Still it is surprising that cachegrind gives us the same results for both implementations of the hadamard matrix multiplication.