#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Include that allows to print result as an image
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

// Default size of image
#define X 1280
#define Y 720
#define MAX_ITER 10000

void calc_mandelbrot(uint8_t image[Y][X]) {
	const float left = -2.5, right = 1;
	const float bottom = -1.0, top = 1;

	double x, y, cx, cy;
	for(unsigned int i = 0; i < Y; i++) {
		for(unsigned int j = 0; j < X; j++) {
			x = 0.0;
			y = 0.0;
			unsigned int iter = 0;
			cx = ((double)j / X) * (right - left) + left;
			cy = ((double)i / Y) * (top - bottom) + bottom;
			while(x * x + y * y <= 4.0 && iter < MAX_ITER) {
				double x_tmp = x * x - y * y + cx;
				y = 2 * x * y + cy;
				x = x_tmp;
				iter++;
			}
			double value = fabs((iter / (float)MAX_ITER)) * 255;
			image[i][j] = value;
		}
	}
}

int main() {
	uint8_t image[Y][X];

	calc_mandelbrot(image);

	const int channel_nr = 1, stride_bytes = 0;
	stbi_write_png("mandelbrot.png", X, Y, channel_nr, image, stride_bytes);
	return EXIT_SUCCESS;
}