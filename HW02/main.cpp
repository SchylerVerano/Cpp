#include <cstdio>
#include "MANDELBROT.H"
//HW02

int main() {
    const int width = 100;  // Terminal width
    const int height = 50; //Terminal height
    const int max_iter = 1000; //Max iterations

    double a_min = -2.5;
    double a_max = 1.5;
    double b_min = -1.0;
    double b_max = 1.0;
    
    for (int row =0; row <height; row++){
        double b = b_max - (b_max - b_min) * row / (height - 1);

        for (int col =0; col < width; col++){
            double a = a_min + (a_max - a_min) * col / (width - 1);

            int iter = mandelbrot_iterations(a, b, max_iter);
            
            if (iter == max_iter){
                printf("*"); //It is in the set
            }else {
                printf(" "); //escaped
            }

        }
        printf("\n");
    }
    return 0;
}
