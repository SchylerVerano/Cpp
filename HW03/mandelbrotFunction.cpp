#include "MANDELBROT.H"
#include <cmath>


void mandelbrot_step(double* x, double* y, double a, double b) {
    double x_new = (*x) * (*x) - (*y) * (*y) + a;
    double y_new = 2 * (*x) * (*y) + b;

    *x = x_new;
    *y = y_new;
}

int mandelbrot_iterations(double a, double b, int max_iter) {
    double x = 0.0, y = 0.0;
    int iter = 0;

    while (x*x + y*y <= 4.0 && iter < max_iter) {
        mandelbrot_step(&x, &y, a, b);
        iter++;
    }

    return iter;
}
