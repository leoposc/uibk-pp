#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define N 9999
#define TILE_SIZE 64 / sizeof(double)
#define BLOCK_SIZE 256

// apply loop unswitching
void c_solution(int* a, int* b, int* c) {
	if(N % 2) {
		for(int i = 0; i < N; ++i) {
			a[i] = b[i] + 5;
		}
	} else {
		for(int i = 0; i < N; ++i) {
			a[i] = c[i] + 5;
		}
	}
}


int main() {
	int ca[N], cb[N], cc[N];

	for(int i = 0; i < N; i++) {
		ca[i] = i;
		cb[i] = i;
		cc[i] = i;
	}

	c_solution(ca, cb, cc);

	double sum_control = 0;
	for(int i = 0; i < N; i++) {
		
		sum_control += ca[i];
		sum_control += cb[i];
		sum_control += cc[i];

	}


	printf("sum_control: %d\n", sum_control);
	return 0;
}