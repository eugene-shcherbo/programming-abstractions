#include <iostream>
#include <string>
#include "console.h"
#include "strlib.h"
#include "stack.h"
using namespace std;

int main() {
    collections::Stack<string> strings;
    assert(strings.size() == 0);

    for (int i = 0; i < 20; i++) {
        strings.push(integerToString(i));
    }
    assert(strings.size() == 20);
    assert(strings.peek() == "19");

    for (int i = 0; i < 20; i++) {
        strings.pop();
    }
    assert(strings.size() == 0);

    cout << "All the tests are passes sucessfully.." << endl;

    return 0;
}
