#include <iostream>
#include <string>
#include "FileStreamBuf.h"

int main()
{
    const char* fname = "fsb_output.txt";
    {
        FILE* fw = std::fopen(fname, "wb+");
        if (!fw) {
            std::perror("fopen write failed");
            return 1;
        }
        FileStreamBuf fsb_write(fw, 4);
        std::ostream out(&fsb_write);
        out << "Testing FileStreamBuf output...\n";
        out << "0123456789ABCDEF\n";
        out << "End of small-buffer test.\n";
        out.flush();
    }

    FILE* fr = std::fopen(fname, "rb");
    if (!fr) {
        std::perror("fopen read failed");
        return 1;
    }
    FileStreamBuf fsb_read(fr, 4);
    std::istream in(&fsb_read);
    std::string line;
    while (std::getline(in, line)) {
        std::cout << line << "\n";
    }
    return 0;
}
