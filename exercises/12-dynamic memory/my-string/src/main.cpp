#include <iostream>
#include "console.h"
#include "mystring.h"
using namespace std;

int main() {
    MyString empty("");
    assert(empty.length() == 0);

    MyString helloWorld("hello world");
    assert(helloWorld.substr(2, 3).toString() == "llo");
    assert(helloWorld.substr(2).toString() == "llo world");
    assert(helloWorld[0] == 'h');
    assert(helloWorld[helloWorld.length() - 1] == 'd');

    helloWorld[0] = 'd';
    assert(helloWorld[0] == 'd');
    helloWorld[0] = 'h';

    MyString copy = helloWorld;
    copy[0] = 'd';
    assert(copy[0] == 'd');
    assert(helloWorld[0] == 'h');

    copy = helloWorld;
    copy[0] = 'd';
    assert(copy[0] == 'd');
    assert(helloWorld[0] == 'h');

    assert((helloWorld + helloWorld).toString() == "hello worldhello world");
    assert(helloWorld.toString() == "hello world");

    assert((helloWorld += helloWorld).toString() == "hello worldhello world");
    assert(helloWorld.toString() == "hello worldhello world");

    assert(helloWorld == helloWorld);
    assert(copy != helloWorld);

    MyString big("aaab");
    MyString little("zalo");
    MyString less("abba");
    assert(little < big);
    assert(less < big);
    assert(empty < big);

    assert(big > little);
    assert(big > less);
    assert(big > empty);

    cout << "All the tests are passed.." << endl;

    return 0;
}
