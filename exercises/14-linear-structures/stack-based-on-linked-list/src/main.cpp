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
        assert(strings.peek() == integerToString(20 - 1 - i));
        strings.pop();
    }
    assert(strings.size() == 0);

    for (int i = 0; i < 20; i++) {
        strings.push(integerToString(i));
    }

    collections::Stack<string> copy = strings;
    copy.push("hello world");
    assert(strings.peek() == "19");
    assert(copy.peek() == "hello world");
    assert(copy.pop() == "hello world");
    assert(copy.pop() == "19");

    copy = strings;
    copy.push("hello world");
    assert(strings.peek() == "19");
    assert(copy.peek() == "hello world");
    assert(copy.pop() == "hello world");
    assert(copy.pop() == "19");

    copy.clear();
    assert(copy.size() == 0);

    cout << "All the tests are passes sucessfully.." << endl;

    return 0;
}
