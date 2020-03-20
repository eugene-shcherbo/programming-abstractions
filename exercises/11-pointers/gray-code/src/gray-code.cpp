#include <iostream>
#include "vector.h"
#include "console.h"

using namespace std;

void generateGrayCode(int nBits);
void generateGrayCode(int nBits, Vector<string>& codes);

int main() {
    generateGrayCode(2);

    cout << endl << endl;

    generateGrayCode(3);

    return 0;
}

void generateGrayCode(int nBits) {
    Vector<string> codes;
    generateGrayCode(nBits, codes);

    for (string code: codes) {
        cout << code << endl;
    }
}

void generateGrayCode(int nBits, Vector<string>& codes) {
    if (nBits <= 1) {
        codes += "0";
        codes += "1";
    } else {
        Vector<string> codesSoFar;
        generateGrayCode(nBits - 1, codesSoFar);

        for (string code: codesSoFar) {
            codes += "0" + code;
        }

        for (int i = codesSoFar.size() - 1; i >= 0; i--) {
            codes += "1" + codesSoFar[i];
        }
    }
}

