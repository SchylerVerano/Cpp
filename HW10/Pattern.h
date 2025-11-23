#ifndef PATTERN_H
#define PATTERN_H

#include <string>

class Pattern {
public:
    std::string pat;
    int count;
    double cumprob;

    Pattern(const std::string& p, int c)
        : pat(p), count(c), cumprob(0.0) {}
};

#endif
