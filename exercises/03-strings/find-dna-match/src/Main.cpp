#include <iostream>
#include "console.h"
using namespace std;

int findDNAMatch(string s1, string s2, int start = 0);
void testFindDNAMatch(string s1, string s2, int start, int expected);
bool doesDNAStrandsMatch(string s1, string s2, int s1Start);
bool doesBaseMatchTo(char base1, char base2);

int main() {
    setConsoleOutputColor("white");
    testFindDNAMatch("TAACGGTACGTC", "TTGCC", 0, 1);
    testFindDNAMatch("TAACGGTACGTC", "TGC", 0, 2);
    testFindDNAMatch("TAACGGTACGTC", "TGC", 3, 7);
    return 0;
}

void testFindDNAMatch(string s1, string s2, int start, int expected) {
    auto actual = findDNAMatch(s1, s2, start);
    cout << "Strand 1: " << s1 << endl
         << "Strand 2: " << s2 << endl
         << "Can be attached in: " << actual << endl
         << "Result: " << (expected == actual ? "SUCCESS" : "FAILED") << endl;
}

int findDNAMatch(string s1, string s2, int start) {
    auto n1 = s1.length();
    auto n2 = s2.length();
    auto longerDna = n1 > n2 ? s1 : s2;
    auto shorterDna = n1 <  n2 ? s1 : s2;

    auto longerIndex = start;

    while (longerIndex < longerDna.length()) {
        auto longerBase = longerDna[longerIndex];
        auto shorterBase = shorterDna[0];

        if (doesDNAStrandsMatch(longerDna, shorterDna, longerIndex)) {
            return longerIndex;
        } else {
            ++longerIndex;
        }
    }

    return -1;
}

bool doesDNAStrandsMatch(string s1, string s2, int s1Start) {
    for (int i = s1Start, j = 0; i < s1.length(); ++i, ++j) {
        if (!doesBaseMatchTo(s1[i], s2[j]))
            return false;
        else if (j == s2.length() - 1)
            return true;
    }
    return false;
}

bool doesBaseMatchTo(char base1, char base2) {
    return (base1 == 'C' && base2 == 'G')
            || (base1 == 'G' && base2 == 'C')
            || (base1 == 'A' && base2 == 'T')
            || (base1 == 'T' && base2 == 'A');
}
