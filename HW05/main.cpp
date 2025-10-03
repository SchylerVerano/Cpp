#include <cstdio>
#include <cstdlib>
#include "mandelbrot.h"

int main() {
    const int width = 800;
    const int height = 600;
    const int max_iter = 1000;

    double a_min = -2.5, a_max = 1.5;
    double b_min = -1.0, b_max = 1.0;

    // Allocate 2D array using Numerical Recipes trick
    int** arr = new int*[height];
    arr[0] = new int[width * height];
    for (int i = 1; i < height; i++) {
        arr[i] = arr[0] + i * width;
    }

    // Fill with Mandelbrot iteration counts
    fill_mandelbrot(arr, width, height, a_min, a_max, b_min, b_max, max_iter);

    // Create 1D RGB buffer
    unsigned char* img = new unsigned char[width * height * 3];
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            int iter = arr[row][col];
            unsigned char color = (iter == max_iter) ? 0 : (iter % 256);
            int idx = (row * width + col) * 3;
            img[idx]     = color; // R
            img[idx + 1] = color; // G
            img[idx + 2] = color; // B
        }
    }

    // Write image to file
    write_ppm("mandelbrot.ppm", img, width, height);

    // Free memory
    delete[] arr[0];
    delete[] arr;
    delete[] img;

    printf("Mandelbrot image written to mandelbrot.ppm\n");
    return 0;
}
