#include "Image.H"

bool Image::readPPM(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Error: Cannot open file " << filename << std::endl;
        return false;
    }

    std::string format;
    file >> format;
    if (format != "P6") {
        std::cerr << "Error: Unsupported PPM format" << std::endl;
        return false;
    }

    file >> width >> height;
    int maxVal;
    file >> maxVal;
    file.ignore(); // skip newline

    pixels.resize(width * height * 3);
    file.read(reinterpret_cast<char*>(pixels.data()), pixels.size());
    return true;
}

bool Image::writePPM(const std::string& filename) const {
    std::ofstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Error: Cannot write to file " << filename << std::endl;
        return false;
    }

    file << "P6\n" << width << " " << height << "\n255\n";
    file.write(reinterpret_cast<const char*>(pixels.data()), pixels.size());
    return true;
}

Image& Image::operator+=(int value) {
    for (auto& pixel : pixels) {
        int newValue = static_cast<int>(pixel) + value;
        pixel = static_cast<unsigned char>(std::clamp(newValue, 0, 255));
    }
    return *this;
}
