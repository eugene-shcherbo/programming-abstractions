#include <iostream>
#include <fstream>
#include <iomanip>
#include <cctype>
#include "console.h"
#include "error.h"

using namespace std;

static constexpr uint ALPHABET_SIZE = 26;

static constexpr uint ROMAN_LOOKUP[26] {
    'A', 'B', 100, 500, 'E', 'F', 'G', 'H', 1, 'J', 'K', 50, 1000,
    'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 5, 'W', 10, 'Y', 'Z'
};

uint getLetterValue(char letter);

uint romanToDecimal(const string& str);
void testRomanToDecimal();

int main() {
    testRomanToDecimal();
    cout << "All tests passed succesfully..." << endl;
    return 0;
}

void testRomanToDecimal() {
    assert(romanToDecimal("LXX") == 70);
    assert(romanToDecimal("MCMLXIX") == 1969);
}

uint getLetterValue(char letter) {
    auto index = static_cast<uint>(toupper(letter) - 'A');
    if (index >= ALPHABET_SIZE) error("Unknown letter");
    return ROMAN_LOOKUP[index];
}

uint romanToDecimal(const std::string& str) {
    int total = 0;

    for (size_t i = 1; i < str.size(); i++) {
        uint curr = getLetterValue(str[i]);
        uint prev = getLetterValue(str[i - 1]);

        total += curr > prev ? -prev : prev;
    }

    total += getLetterValue(str[str.size() - 1]);

    return static_cast<uint>(total);
}
