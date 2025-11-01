#include <iostream>
#include "Image.H"

int main() {
    Image img;

    if (!img.readPPM("test.ppm")) {
        std::cerr << "Failed to load image.\n";
        return 1;
    }

    std::cout << "Image loaded (" << img.getWidth() << "x" << img.getHeight() << ").\n";

    img += 50; // brighten the image

    if (!img.writePPM("brightened.ppm")) {
        std::cerr << "Failed to save image.\n";
        return 1;
    }

    std::cout << "Brightened image saved as brightened.ppm\n";
    return 0;
}
