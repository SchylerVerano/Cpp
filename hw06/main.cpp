#include <iostream>
#include <string>
#include "JPEGfunctions.H"

int main() {
    std::string inputFile = "test.ppm";
    std::string outputFile = "output.jpg";

    try {
        // Read PPM image
        Image img = readPPM(inputFile);

        // Write JPEG image
        writeJPEG(outputFile, img);

        std::cout << "Conversion complete! Saved as " << outputFile << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
