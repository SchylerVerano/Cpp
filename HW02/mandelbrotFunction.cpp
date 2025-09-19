#include "MANDELBROT.H"
#include <cmath>

int mandelbrot_iterations(double a, double b, int max_iter) {
    double x = 0.0;
    double y = 0.0;
    int iter = 0;

    while (x*x + y*y <= 4.0 && iter < max_iter) {
        double x_new = x*x - y*y + a;
        double y_new = 2*x*y + b;

        // Update x and y
        x = x_new;
        y = y_new;

        iter++;
    }

    return iter;
}