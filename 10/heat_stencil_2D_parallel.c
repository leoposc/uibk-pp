#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <omp.h>
#include <string.h>

#define RESOLUTION_WIDTH 50
#define RESOLUTION_HEIGHT 50

#define PERROR fprintf(stderr, "%s:%d: error: %s\n", __FILE__, __LINE__, strerror(errno))
#define PERROR_GOTO(label) \
	do { \
		PERROR; \
		goto label; \
	} while (0)

typedef double value_t;
typedef value_t *Vector;

// -- vector utilities --

#define IND(y, x) ((y) * (N) + (x))

void printTemperature(double *m, int N, int M);

double calc_nearby_head_diff(Vector A, Vector B, int N);

// -- simulation code ---

int main(int argc, char **argv) {
    // 'parsing' optional input parameter = problem size
    int N = 200;
    if (argc > 1) {
        N = atoi(argv[1]);
    }
    int T = N * 10;
    printf("Computing heat-distribution for room size %dX%d for T=%d timesteps\n", N, N, T);

    // ---------- setup ----------

    // create a buffer for storing temperature fields
    Vector A =  malloc(sizeof(double) * N * N);
    if(!A) PERROR_GOTO(error_a);
    Vector B = malloc(sizeof(double) * N * N);
    if(!B) PERROR_GOTO(error_b);
    Vector H;


    // set up initial conditions in A
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[IND(i,j)] = 273; // temperature is 0° C everywhere (273 K)
            B[IND(i,j)] = 273; // temperature is 0° C everywhere (273 K)
        }
    }

    // and there is a heat source
    int source_x = N / 4;
    int source_y = N / 4;
    A[IND(source_x,source_y)] = 273.0 + 60;

    printf("Initial:");
    printTemperature(A, N, N);
    printf("\n");

    // ---------- compute ----------
    double start = omp_get_wtime();

    // for each time step ..
    for (int t = 0; t < T; t++) {

        calc_nearby_head_diff(A, B, N);
        
        // make sure the heat source stays the same
        B[IND(source_x,source_y)] = 273.0 + 60;

        // swap matrices (just pointers, not content)
        H = A;
        A = B;
        B = H;

        // every 1000 steps show intermediate step
        if (!(t % 1000)) {
            printf("Step t=%d\n", t);
            printTemperature(A, N, N);
            printf("\n");
        }
    }

    double end = omp_get_wtime();

    printf("$!%s: %f\n", argv[0], end - start);

    // ---------- check ----------

    printf("Final:");
    printTemperature(A, N, N);
    printf("\n");

    // simple verification if nowhere the heat is more then the heat source
    int success = 1;
    for (long long i = 0; i < N; i++) {
        for (long long j = 0; j < N; j++) {
            double temp = A[IND(i,j)];
            if (273 <= temp && temp <= 273 + 60)
                continue;
            printf("failure at %lld, %lld: %f\n", i, j, A[IND(i,j)]);
            success = 0;
            break;
        }
    }

    printf("Verification: %s\n", (success) ? "OK" : "FAILED");

    // todo ---------- cleanup ----------
    error_b:
    free(B);
    error_a:
    free(A);
    return (success) ? EXIT_SUCCESS : EXIT_FAILURE;
}


double calc_nearby_head_diff(Vector A, Vector B, int N) {
#pragma omp parallel for collapse(2)
    for (int y = 0; y < N; y++) {
        for (int x = 0; x < N; x++) {
            double t = A[IND(x,y)];
            double t_n = (x == 0) ? t : A[IND(x-1,y)];
            double t_s = (x == N-1) ? t : A[IND(x+1,y)];
            double t_w = (y == 0) ? t : A[IND(x,y-1)];
            double t_e = (y == N-1) ? t : A[IND(x,y+1)];

            B[IND(y,x)] = (t_n + t_s + t_w + t_e) / 4.0;
        }
    }
}


void printTemperature(double *m, int N, int M) {
    const char *colors = " .-:=+*^X#%@";
    const int numColors = 12;

    // boundaries for temperature (for simplicity hard-coded)
    const double max = 273 + 30;
    const double min = 273 + 0;

    // set the 'render' resolution
    int W = RESOLUTION_WIDTH;
    int H = RESOLUTION_HEIGHT;

    // step size in each dimension
    int sW = N / W;
    int sH = M / H;

    // upper wall
    printf("\t");
    for (int u = 0; u < W + 2; u++) {
        printf("X");
    }
    printf("\n");
    // room
    for (int i = 0; i < H; i++) {
        // left wall
        printf("\tX");
        // actual room
        for (int j = 0; j < W; j++) {
            // get max temperature in this tile
            double max_t = 0;
            for (int x = sH * i; x < sH * i + sH; x++) {
                for (int y = sW * j; y < sW * j + sW; y++) {
                    max_t = (max_t < m[IND(x,y)]) ? m[IND(x,y)] : max_t;
                }
            }
            double temp = max_t;

            // pick the 'color'
            int c = ((temp - min) / (max - min)) * numColors;
            c = (c >= numColors) ? numColors - 1 : ((c < 0) ? 0 : c);

            // print the average temperature
            printf("%c", colors[c]);
        }
        // right wall
        printf("X\n");
    }
    // lower wall
    printf("\t");
    for (int l = 0; l < W + 2; l++) {
        printf("X");
    }
    printf("\n");
}
