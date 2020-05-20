#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include "console.h"
#include "morseencoding.h"

using namespace std;

int main() {
    MorseEncoding encoding;

    cout << ".-.. is " << encoding.getMorseCodeLetter(".-..") << endl;

    return 0;
}
