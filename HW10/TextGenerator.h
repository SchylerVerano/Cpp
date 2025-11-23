#ifndef TEXTGENERATOR_H
#define TEXTGENERATOR_H

#include <string>
#include <unordered_map>
#include <vector>
#include "Pattern.h"

class TextGenerator {
public:
    TextGenerator();
    bool loadTrainingFile(const std::string& filename);
    void buildCounts(int length);
    void buildLookup(int length);
    void computeCumulativeProbabilities();
    std::string generate(int outChars, int length);
    std::vector<std::string> availablePrefixes() const;
private:
    std::string training;
    std::unordered_map<std::string,int> counts;
    std::unordered_map<std::string,std::vector<Pattern>> lookup;
};

#endif
