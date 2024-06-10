#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define N 9999
#define TILE_SIZE 64 / sizeof(double)
#define BLOCK_SIZE 256


void c(int* a, int* b, int* c) {
	for(int i = 0; i < N; ++i) {
		if(N % 2) {
			a[i] = b[i] + 5;
		} else {
			a[i] = c[i] + 5;
		}
	}
}

int main() {

	int va[N], vb[N], vc[N];

	for(int i = 0; i < N; i++) {
		va[i] = i;
		vb[i] = i;
		vc[i] = i;
	}



	c(va, vb, vc);
	

	int sum = 0;
	for(int i = 0; i < N; i++) {
		sum += va[i];
		sum += vb[i];
		sum += vc[i];
		
	}

	printf("sum: %d\n", sum);
	
	return 0;
}