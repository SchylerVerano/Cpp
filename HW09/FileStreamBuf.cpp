#include "FileStreamBuf.h"
#include <cstring>
#include <stdexcept>

using traits = std::streambuf::traits_type;

FileStreamBuf::FileStreamBuf(FILE* file, std::size_t bufsize)
    : file_(file), buf_(nullptr), bufsize_(bufsize)
{
    if (!file_) throw std::runtime_error("null FILE*");
    buf_ = new char[bufsize_];
    setp(buf_, buf_ + bufsize_);
    setg(buf_, buf_ + bufsize_, buf_ + bufsize_);
}

FileStreamBuf::~FileStreamBuf()
{
    sync();
    if (file_) {
        fclose(file_);
        file_ = nullptr;
    }
    delete[] buf_;
}

std::streambuf::int_type FileStreamBuf::overflow(std::streambuf::int_type c)
{
    char* pbeg = pbase();
    char* pend = pptr();
    std::ptrdiff_t n = pend - pbeg;
    if (n > 0) {
        std::size_t written = fwrite(pbeg, 1, static_cast<std::size_t>(n), file_);
        if (written != static_cast<std::size_t>(n)) return traits::eof();
    }
    setp(buf_, buf_ + bufsize_);
    if (c != traits::eof()) {
        char ch = traits::to_char_type(c);
        *pptr() = ch;
        pbump(1);
        return traits::to_int_type(ch);
    }
    return traits::not_eof(c);
}

int FileStreamBuf::sync()
{
    char* pbeg = pbase();
    char* pend = pptr();
    std::ptrdiff_t n = pend - pbeg;
    if (n > 0) {
        std::size_t written = fwrite(pbeg, 1, static_cast<std::size_t>(n), file_);
        if (written != static_cast<std::size_t>(n)) return -1;
    }
    if (fflush(file_) != 0) return -1;
    setp(buf_, buf_ + bufsize_);
    return 0;
}

std::streambuf::int_type FileStreamBuf::underflow()
{
    if (gptr() < egptr()) return traits::to_int_type(*gptr());
    std::size_t got = fread(buf_, 1, bufsize_, file_);
    if (got == 0) return traits::eof();
    setg(buf_, buf_, buf_ + static_cast<std::ptrdiff_t>(got));
    return traits::to_int_type(*gptr());
}

std::streambuf::int_type FileStreamBuf::uflow()
{
    int_type c = underflow();
    if (c == traits::eof()) return c;
    gbump(1);
    return c;
}
