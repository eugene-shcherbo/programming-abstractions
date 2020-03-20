#include <iostream>
#include "console.h"

using namespace std;

void generateBinaryCodes(int nBits, string prefix = "");

int main() {
    generateBinaryCodes(3);

    cout << endl << endl;

    generateBinaryCodes(4);

    return 0;
}

void generateBinaryCodes(int nBits, string prefix) {
    if (nBits <= 0) {
        cout << prefix << endl;
    } else {
        generateBinaryCodes(nBits - 1, prefix + "0");
        generateBinaryCodes(nBits - 1, prefix + "1");
    }
}
