#include <iostream>
#include <string>
#include "TextGenerator.h"

using namespace std;

int main() {
    const int patternLength = 4;
    const int outputLength  = 1000;

    TextGenerator generator;

    // Load training file
    if (!generator.loadTrainingFile("training.txt")) {
        cerr << "Error: Could not open training.txt\n";
        return 1;
    }

    // Build internal structures
    generator.buildCounts(patternLength);
    generator.buildLookup(patternLength);
    generator.computeCumulativeProbabilities();

    // Generate text
    cout << "Generated Text:\n\n";
    string output = generator.generate(outputLength, patternLength);
    cout << output << "\n";

    return 0;
}
