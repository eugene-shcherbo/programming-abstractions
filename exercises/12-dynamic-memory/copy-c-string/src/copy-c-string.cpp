#include <iostream>
#include "vector.h"
#include "strlib.h"
#include "console.h"
using namespace std;

char* copyCString(char* str);
unsigned long strlen(char* str);

int main() {
    char* str = "hello world";
    cout << "Copy of " << str << " is " << copyCString(str) << endl;

    return 0;
}

char* copyCString(char* str) {
    unsigned long len = strlen(str) + 1;
    char* dst = new char[len];

    for (int i = 0; i < len; i++) {
        *(dst + i) = *(str + i);
    }

    return dst;
}

unsigned long strlen(char* str) {
    char *cp;
    for (cp = str; *cp != '\0'; cp++);
    return cp - str;
}

