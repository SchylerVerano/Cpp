#include "mandelbrot.h"
#include <cmath>
#include <cstdio>

// Compute iterations for a single point
int mandelbrot_iterations(double a, double b, int max_iter) {
    double x = 0.0, y = 0.0;
    int iter = 0;

    while (x*x + y*y <= 4.0 && iter < max_iter) {
        double x_new = x*x - y*y + a;
        double y_new = 2*x*y + b;
        x = x_new;
        y = y_new;
        iter++;
    }

    return iter;
}

// Fill 2D array with iteration counts
void fill_mandelbrot(int** arr, int width, int height,
                     double a_min, double a_max,
                     double b_min, double b_max,
                     int max_iter) {
    for (int row = 0; row < height; row++) {
        double b = b_max - (b_max - b_min) * row / (height - 1);
        for (int col = 0; col < width; col++) {
            double a = a_min + (a_max - a_min) * col / (width - 1);
            arr[row][col] = mandelbrot_iterations(a, b, max_iter);
        }
    }
}

// Write PPM image
void write_ppm(const char* filename, unsigned char* img,
               int width, int height) {
    FILE* fp = fopen(filename, "wb");
    if (!fp) {
        perror("Failed to open file");
        return;
    }
    fprintf(fp, "P6\n%d %d\n255\n", width, height);
    fwrite(img, 1, width * height * 3, fp);
    fclose(fp);
}
