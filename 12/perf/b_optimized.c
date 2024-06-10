#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define N 9999

// apply loop invariant code motion
void b_solution(double* a) {
	const double c = hypot(0.3, 0.4);
	for(int i = 0; i < N; i++) {
		a[i] *= c;
	}
}


int main() {

	double cda[N];


	for(int i = 0; i < N; i++) {

		cda[i] = i;
	}


	b_solution(cda);

	double sum_d_control = 0;
	for(int i = 0; i < N; i++) {

		sum_d_control += cda[i];
	}

	printf("sum_d_control: %f\n", sum_d_control);

	return 0;
}