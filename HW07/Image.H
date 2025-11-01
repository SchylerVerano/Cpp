#ifndef IMAGE_H
#define IMAGE_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>

class Image {
private:
    int width;
    int height;
    std::vector<unsigned char> pixels; // RGBRGBRGB...

public:
    Image() : width(0), height(0) {}
    Image(int w, int h) : width(w), height(h), pixels(w * h * 3) {}
    ~Image() = default; // vector cleans itself up

    bool readPPM(const std::string& filename);
    bool writePPM(const std::string& filename) const;

    Image& operator+=(int value);

    int getWidth() const { return width; }
    int getHeight() const { return height; }
};

#endif
