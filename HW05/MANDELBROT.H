#ifndef MANDELBROT_H
#define MANDELBROT_H

int mandelbrot_iterations(double a, double b, int max_iter);

// Function to fill a 2D array with Mandelbrot iterations
void fill_mandelbrot(int** arr, int width, int height,
                     double a_min, double a_max,
                     double b_min, double b_max,
                     int max_iter);

// Function to write a PPM file from an RGB buffer
void write_ppm(const char* filename, unsigned char* img,
               int width, int height);

#endif
