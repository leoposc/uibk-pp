#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define N 9999


// apply loop unrolling
void a_solution(int* a, int* b) {
	for(int i = 0; i < N - 2; i += 2) {
		a[i] = b[i] + b[i + 1];
		a[i + 1] = b[i + 1] + b[i + 2];
	}
}

int main() {

	int ca[N], cb[N];

	for(int i = 0; i < N; i++) {
		ca[i] = i;
		cb[i] = i;
	}

	a_solution(ca, cb);

	int sum_control = 0;
	for(int i = 0; i < N; i++) {
		sum_control += ca[i];
		sum_control += cb[i];
	}

	printf("sum_control: %d\n", sum_control);
	return 0;
}

