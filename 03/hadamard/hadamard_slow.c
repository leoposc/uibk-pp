#include <stdio.h>
#include <stdlib.h>

int main() {

    const int matrix_sz = 10000;

    int a[ matrix_sz][ matrix_sz];
    int b[ matrix_sz][ matrix_sz];
    int c[ matrix_sz][ matrix_sz];

    for(size_t j = 0; j < matrix_sz; ++j) {
        for(size_t i = 0; i < matrix_sz; ++i) {
            c[i][j] = a[i][j] * b[i][j];
        }
    }

    return EXIT_SUCCESS;

}