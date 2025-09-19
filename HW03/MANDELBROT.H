#ifndef MANDELBROT_H
#define MANDELBROT_H

void mandelbrot_step(double* x, double* y, double a, double b);

int mandelbrot_iterations(double a, double b, int max_iter);

#endif // MANDELBROT_H
