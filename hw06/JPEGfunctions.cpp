#include "JPEGfunctions.H"
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <jpeglib.h>

Image readPPM(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) throw std::runtime_error("Cannot open PPM file!");

    std::string format;
    file >> format;
    if (format != "P6") throw std::runtime_error("Unsupported PPM format (must be P6)!");

    Image img;
    file >> img.width >> img.height;
    int maxVal;
    file >> maxVal;
    file.ignore(); // skip newline/whitespace

    if (maxVal != 255)
        std::cerr << "Warning: only maxVal=255 supported, image may not display correctly.\n";

    img.data.resize(img.width * img.height * 3);
    file.read(reinterpret_cast<char*>(img.data.data()), img.data.size());

    if (!file) throw std::runtime_error("Error reading pixel data from PPM file!");

    return img;
}

void writeJPEG(const std::string& filename, const Image& img, int quality) {
    FILE* outfile = fopen(filename.c_str(), "wb");
    if (!outfile) throw std::runtime_error("Cannot open output JPEG file!");

    jpeg_compress_struct cinfo;
    jpeg_error_mgr jerr;

    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_compress(&cinfo);
    jpeg_stdio_dest(&cinfo, outfile);

    cinfo.image_width = img.width;
    cinfo.image_height = img.height;
    cinfo.input_components = 3;
    cinfo.in_color_space = JCS_RGB;

    jpeg_set_defaults(&cinfo);
    jpeg_set_quality(&cinfo, quality, TRUE);

    jpeg_start_compress(&cinfo, TRUE);

    JSAMPROW row_pointer[1];
    int row_stride = img.width * 3;

    while (cinfo.next_scanline < cinfo.image_height) {
        row_pointer[0] = (unsigned char*)&img.data[cinfo.next_scanline * row_stride];
        jpeg_write_scanlines(&cinfo, row_pointer, 1);
    }

    jpeg_finish_compress(&cinfo);
    fclose(outfile);
    jpeg_destroy_compress(&cinfo);
}
