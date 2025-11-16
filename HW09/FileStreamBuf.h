#ifndef FILESTREAMBUF_H
#define FILESTREAMBUF_H

#include <streambuf>
#include <cstdio>
#include <cstddef>

class FileStreamBuf : public std::streambuf {
public:
    FileStreamBuf(FILE* file, std::size_t bufsize);
    ~FileStreamBuf();

    FileStreamBuf(const FileStreamBuf&) = delete;
    FileStreamBuf& operator=(const FileStreamBuf&) = delete;
    FileStreamBuf(FileStreamBuf&&) = delete;
    FileStreamBuf& operator=(FileStreamBuf&&) = delete;

protected:
    using traits = std::streambuf::traits_type;
    using int_type = traits::int_type;

    int_type overflow(int_type c) override;
    int sync() override;
    int_type underflow() override;
    int_type uflow() override;

private:
    FILE* file_;
    char* buf_;
    std::size_t bufsize_;
};

#endif
