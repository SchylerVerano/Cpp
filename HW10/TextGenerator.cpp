#include "TextGenerator.h"
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <algorithm>
#include <ctime>

TextGenerator::TextGenerator() : training(), counts(), lookup() {}

bool TextGenerator::loadTrainingFile(const std::string& filename) {
    std::ifstream ifs(filename);
    if (!ifs) return false;
    std::string tok;
    std::ostringstream oss;
    bool first = true;
    while (ifs >> tok) {
        if (!first) oss << ' ';
        oss << tok;
        first = false;
    }
    training = oss.str();
    return true;
}

void TextGenerator::buildCounts(int length) {
    counts.clear();
    if (length <= 0) return;
    if ((int)training.size() < length) return;
    for (size_t i = 0; i + length <= training.size(); ++i) {
        std::string sub = training.substr(i, length);
        auto it = counts.find(sub);
        if (it == counts.end()) counts.emplace(sub, 1);
        else ++(it->second);
    }
}

void TextGenerator::buildLookup(int length) {
    lookup.clear();
    if (length <= 1) return;
    for (auto &kv : counts) {
        const std::string& full = kv.first;
        int cnt = kv.second;
        std::string prefix = full.substr(0, length - 1);
        auto &vec = lookup[prefix];
        vec.emplace_back(full, cnt);
    }
    for (auto &kv : lookup) {
        auto &vec = kv.second;
        std::sort(vec.begin(), vec.end(), [](const Pattern& a, const Pattern& b){
            if (a.pat != b.pat) return a.pat < b.pat;
            return a.count > b.count;
        });
    }
}

void TextGenerator::computeCumulativeProbabilities() {
    for (auto &kv : lookup) {
        auto &vec = kv.second;
        long long total = 0;
        for (auto &p : vec) total += p.count;
        if (total == 0) {
            for (auto &p : vec) p.cumprob = 0.0;
            continue;
        }
        long long running = 0;
        for (auto &p : vec) {
            running += p.count;
            p.cumprob = static_cast<double>(running) / static_cast<double>(total);
        }
        if (!vec.empty()) vec.back().cumprob = 1.0;
    }
}

std::vector<std::string> TextGenerator::availablePrefixes() const {
    std::vector<std::string> out;
    out.reserve(lookup.size());
    for (auto &kv : lookup) out.push_back(kv.first);
    return out;
}

std::string TextGenerator::generate(int outChars, int length) {
    if (length <= 1 || lookup.empty()) return std::string();
    std::vector<std::string> keys;
    for (auto &kv : lookup) keys.push_back(kv.first);
    if (keys.empty()) return std::string();
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    std::string current = keys[std::rand() % keys.size()];
    std::string result = current;
    while ((int)result.size() < outChars) {
        std::string pref = result.substr(result.size() - (length - 1), length - 1);
        auto it = lookup.find(pref);
        if (it == lookup.end()) {
            pref = keys[std::rand() % keys.size()];
            it = lookup.find(pref);
            if (it == lookup.end()) break;
        }
        double r = (double)std::rand() / (double)RAND_MAX;
        const auto &vec = it->second;
        const Pattern* chosen = nullptr;
        for (const auto &p : vec) {
            if (r <= p.cumprob) {
                chosen = &p;
                break;
            }
        }
        if (!chosen) chosen = &vec.back();
        char nextc = chosen->pat.back();
        result.push_back(nextc);
    }
    if ((int)result.size() > outChars) result.resize(outChars);
    return result;
}
