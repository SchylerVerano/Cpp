#include <cstdio>
#include <cstdlib>

// Function to read a PPM (P6) image
bool readPPM(const char* filename, unsigned char*& data, int& width, int& height) {
    FILE* file = fopen(filename, "rb");
    if (!file) {
        printf("Error: Cannot open file %s\n", filename);
        return false;
    }

    char magic[3];
    if (fscanf(file, "%2s", magic) != 1 || magic[0] != 'P' || magic[1] != '6') {
        printf("Error: Unsupported PPM format (must be P6)\n");
        fclose(file);
        return false;
    }

    if (fscanf(file, "%d %d", &width, &height) != 2) {
        printf("Error: Cannot read width and height\n");
        fclose(file);
        return false;
    }

    int maxVal;
    if (fscanf(file, "%d", &maxVal) != 1 || maxVal != 255) {
        printf("Error: Only maxVal=255 is supported\n");
        fclose(file);
        return false;
    }

    fgetc(file);

    size_t dataSize = 3 * width * height;
    data = (unsigned char*)malloc(dataSize);
    if (!data) {
        printf("Error: Memory allocation failed\n");
        fclose(file);
        return false;
    }

    if (fread(data, 1, dataSize, file) != dataSize) {
        printf("Error: Not enough pixel data in file\n");
        free(data);
        fclose(file);
        return false;
    }

    fclose(file);
    return true;
}

// Function to write a PPM (P6) image
bool writePPM(const char* filename, unsigned char* data, int width, int height) {
    FILE* file = fopen(filename, "wb");
    if (!file) {
        printf("Error: Cannot write to file %s\n", filename);
        return false;
    }

    fprintf(file, "P6\n%d %d\n255\n", width, height);
    size_t dataSize = 3 * width * height;
    if (fwrite(data, 1, dataSize, file) != dataSize) {
        printf("Error: Failed to write pixel data\n");
        fclose(file);
        return false;
    }

    fclose(file);
    return true;
}


int main() {
    unsigned char* imageData = nullptr;
    int width, height;

    if (readPPM("test.ppm", imageData, width, height)) {
        printf("Image loaded: %dx%d\n", width, height);

        if (writePPM("output.ppm", imageData, width, height)) {
            printf("Image saved as output.ppm\n");
        }

        free(imageData);
    }

    return 0;
}
