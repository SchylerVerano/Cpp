#include <cstdio>
#include <cmath>

int main() {
    double a = 2.0;
    double b = 0.0;

    double x = 0.0;
    double y = 0.0;

    const int max_iter = 1000;  // number of iterations
    int iter = 0;

    while (x*x + y*y <= 4.0 && iter < max_iter) {
        double x_new = x*x - y*y + a;
        double y_new = 2*x*y + b;

        // Update x and y
        x = x_new;
        y = y_new;

        iter++;
    }

    // Print results
    printf("After %d iterations:\n", iter);
    printf("x = %.7f\n", x);
    printf("y = %.7f\n", y);

    if (iter == max_iter) {
        printf("Point (%.3f, %.3f) is bounded (stabilized).\n", a, b);
    } else {
        printf("Point (%.3f, %.3f) escaped.\n", a, b);
    }

    return 0;
}
