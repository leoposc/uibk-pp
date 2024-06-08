#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define N 99
#define TILE_SIZE 64 / sizeof(double)
#define BLOCK_SIZE 64

void a(int* a, int* b) {
	for(int i = 0; i < N - 1; i++) {
		a[i] = b[i] + b[i + 1];
	}
}

// apply loop unrolling
void a_solution(int* a, int* b) {
	for(int i = 0; i < N - 2; i += 2) {
		a[i] = b[i] + b[i + 1];
		a[i + 1] = b[i + 1] + b[i + 2];
	}
}

void b(double* a) {
	for(int i = 0; i < N; i++) {
		a[i] *= hypot(0.3, 0.4);
	}
}

// apply loop invariant code motion
void b_solution(double* a) {
	const double c = hypot(0.3, 0.4);
	for(int i = 0; i < N; i++) {
		a[i] *= c;
	}
}

void c(int* a, int* b, int* c) {
	for(int i = 0; i < N; ++i) {
		if(N % 2) {
			a[i] = b[i] + 5;
		} else {
			a[i] = c[i] + 5;
		}
	}
}

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

void d(int* a, int* b, int* c) {
	int sum_a = 0, sum_b = 0, sum_c = 0;
	for(int i = 0; i < N; ++i) {
		sum_a += a[i];
		sum_b += b[i];
		sum_c += c[i];
	}
	printf("sum_a: %d\n", sum_a);
	printf("sum_b: %d\n", sum_b);
	printf("sum_c: %d\n", sum_c);
}

// apply loop loop fission/ distribution
void d_solution(int* a, int* b, int* c) {
	int sum_a = 0, sum_b = 0, sum_c = 0;
	for(int i = 0; i < N; ++i) {
		sum_a += a[i];
	}
	printf("sum_a: %d\n", sum_a);
	for(int i = 0; i < N; ++i) {
		sum_b += b[i];
	}
	printf("sum_b: %d\n", sum_b);
	for(int i = 0; i < N; ++i) {
		sum_c += c[i];
	}
	printf("sum_c: %d\n", sum_c);
}

void e(int* a) {
	int sum = 0;
	int min = a[0];
	for(int i = 1; i < N; ++i) {
		min = (a[i] < min) ? a[i] : min;
	}
	for(int i = 0; i < N; ++i) {
		sum += a[i];
	}
	printf("min: %d\n", min);
	printf("sum: %d\n", sum);
}

// apply loop peeling and loop fusion/ combination
void e_solution(int* a) {
	int min = a[0];
	int sum = a[0];
	for(int i = 1; i < N; ++i) {
		min = (a[i] < min) ? a[i] : min;
		sum += a[i];
	}
	printf("min: %d\n", min);
	printf("sum: %d\n", sum);
}

void f(int* a, int* b, int* c) {
	for(int i = 0; i < N; i++) {
		if(i % 2) {
			a[i] = b[i] + 4;
		} else {
			a[i] = c[i] + 5;
		}
	}
}

// apply loop splitting
void f_solution(int* a, int* b, int* c) {
	for(int i = 0; i < N + 1; i += 2) {
		a[i] = b[i] + 4;
	}
	for(int i = 1; i < N; i += 2) {
		a[i] = c[i] + 5;
	}
}

void g(double a[BLOCK_SIZE][BLOCK_SIZE], double b[BLOCK_SIZE][BLOCK_SIZE],
       double c[BLOCK_SIZE][BLOCK_SIZE]) {
	for(int i = 0; i < BLOCK_SIZE; i++) {
		for(int j = 0; j < BLOCK_SIZE; j++) {
			for(int k = 0; k < BLOCK_SIZE; k++) {
				c[i][j] = a[i][k] * b[k][j];
			}
		}
	}
}

// apply loop tiling
void g_solution(double a[BLOCK_SIZE][BLOCK_SIZE], double b[BLOCK_SIZE][BLOCK_SIZE],
                double c[BLOCK_SIZE][BLOCK_SIZE]) {
	for(int ii = 0; ii < BLOCK_SIZE; ii += TILE_SIZE) {
		for(int jj = 0; jj < BLOCK_SIZE; jj += TILE_SIZE) {
			for(int kk = 0; kk < BLOCK_SIZE; kk += TILE_SIZE) {
				for(int i = ii; i < ii + TILE_SIZE; i++) {
					for(int j = jj; j < jj + TILE_SIZE; j++) {
						for(int k = kk; k < kk + TILE_SIZE; k++) {
							c[i][j] = a[i][k] * b[k][j];
						}
					}
				}
			}
		}
	}
}

int main() {

	int va[N], vb[N], vc[N];
	int ca[N], cb[N], cc[N];
	double da[N];
	double cda[N];
	double ga[BLOCK_SIZE][BLOCK_SIZE], gb[BLOCK_SIZE][BLOCK_SIZE], gc[BLOCK_SIZE][BLOCK_SIZE];
	double cga[BLOCK_SIZE][BLOCK_SIZE], cgb[BLOCK_SIZE][BLOCK_SIZE], cgc[BLOCK_SIZE][BLOCK_SIZE];

	for(int i = 0; i < N; i++) {
		va[i] = i;
		vb[i] = i;
		vc[i] = i;
		ca[i] = i;
		cb[i] = i;
		cc[i] = i;
		da[i] = i;
		cda[i] = i;
	}

	for(int i = 0; i < BLOCK_SIZE; i++) {
		for(int j = 0; j < BLOCK_SIZE; j++) {
			ga[i][j] = i + j;
			gb[i][j] = i + j;
			gc[i][j] = 0;
			cga[i][j] = i + j;
			cgb[i][j] = i + j;
			cgc[i][j] = 0;
		}
	}

	a(va, vb);
	a_solution(ca, cb);

	b(da);
	b_solution(cda);

	c(va, vb, vc);
	c_solution(ca, cb, cc);

	// d(va, vb, vc);
	// d_solution(ca, cb, cc);

	// e(va);
	// e_solution(ca);

	// f(va, vb, vc);
	// f_solution(ca, cb, cc);

	g(ga, gb, gc);
	g_solution(cga, cgb, cgc);

	int sum = 0;
	int sum_control = 0;
	double sum_d = 0;
	double sum_d_control = 0;
	for(int i = 0; i < N; i++) {
		sum += va[i];
		sum += vb[i];
		sum += vc[i];
		sum_control += ca[i];
		sum_control += cb[i];
		sum_control += cc[i];

		sum_d += da[i];
		sum_d_control += cda[i];
	}

	printf("sum: %d\n", sum);
	printf("sum_control: %d\n", sum_control);
	printf("sum_d: %f\n", sum_d);
	printf("sum_d_control: %f\n", sum_d_control);

	return 0;
}