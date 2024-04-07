#include <stdio.h>
#include <stdlib.h>

int calc_data_cache_misses_fast(const unsigned long int matrix_sz, const unsigned long int cache_line_sz)
{
    const unsigned long int n_way_cache = 8;
    const unsigned long int elem_bits = 4;
    unsigned long int cache_misses = (matrix_sz * matrix_sz * elem_bits) / (cache_line_sz * n_way_cache);
    return cache_misses * 3;
}

int calc_data_cache_misses_slow(const unsigned long int matrix_sz, const unsigned long int cache_line_sz)
{
    const int cache_sz = 4 * 100;

    const double n_way_cache = 8;
    const unsigned int elem_bits = 4;
    unsigned long int row_size = matrix_sz * elem_bits;
    double cache_row_size = cache_line_sz * n_way_cache;
    double cache_hits_per_load = cache_row_size / row_size;
    cache_hits_per_load = cache_hits_per_load < 1 ? 1 : cache_hits_per_load;
    double misses_y = matrix_sz / cache_hits_per_load;

    if ((matrix_sz * matrix_sz * elem_bits) < cache_sz)
    {
        return (matrix_sz / misses_y) * 3;
    }
    else
    {
        return ((matrix_sz / misses_y) * matrix_sz) * 3;
    }
}

int main()
{
    const unsigned long int mat_sz = 1000;
    const unsigned long int cache_line_sz = 64;
    printf("Calculate data cache misses for a %d x %d matrix with a cache line size of %d bits\n", mat_sz, mat_sz, cache_line_sz);
    printf("Fast: %d\n", calc_data_cache_misses_fast(mat_sz, cache_line_sz));
    printf("Slow: %d\n", calc_data_cache_misses_slow(mat_sz, cache_line_sz));

    return EXIT_SUCCESS;
}