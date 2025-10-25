#ifndef JPEGFUNCTIONS_H
#define JPEGFUNCTIONS_H

#include <string>
#include <vector>

struct Image {
    int width;
    int height;
    std::vector<unsigned char> data; // RGBRGBRGB...
};

// Reads a binary P6 PPM file into an Image struct
Image readPPM(const std::string& filename);

// Writes an Image struct to a JPEG file using libjpeg
void writeJPEG(const std::string& filename, const Image& img, int quality = 90);

#endif
