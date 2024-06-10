#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define N 9999
#define TILE_SIZE 64 / sizeof(double)
#define BLOCK_SIZE 256

void b(double* a) {
	for(int i = 0; i < N; i++) {
		a[i] *= hypot(0.3, 0.4);
	}
}


int main() {
	double da[N];
	

	for(int i = 0; i < N; i++) {
		da[i] = i;
	}

	b(da);
	// b_solution(cda);

	double sum_d = 0;
	for(int i = 0; i < N; i++) {

		sum_d += da[i];

	}
	printf("sum_d: %f\n", sum_d);


	return 0;
}