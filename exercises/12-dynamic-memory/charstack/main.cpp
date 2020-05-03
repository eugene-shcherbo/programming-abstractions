#include <iostream>
#include <cassert>

#include "charstack.h"

using namespace std;

void assertEmpty(const CharStack& stack);
void assertNotEmpty(const CharStack& stack, int count);

int main()
{
    CharStack chStack;

    assertEmpty(chStack);

    chStack.push('A');
    assertNotEmpty(chStack, 1);

    assert(chStack.peek() == 'A');
    assert(chStack.pop() == 'A');
    assertEmpty(chStack);

    for (char ch = 'A'; ch <= 'Z'; ch++) {
        chStack.push(ch);
    }

    assertNotEmpty(chStack, 26);

    for (char ch = 'Z'; ch >= 'A'; ch--) {
        assert(chStack.peek() == ch);
        assert(chStack.pop() == ch);
    }

    assertEmpty(chStack);

    for (char ch = 'A'; ch <= 'Z'; ch++) {
        chStack.push(ch);
    }

    chStack.clear();
    assertEmpty(chStack);

    CharStack chStack2 = chStack;
    chStack2 = chStack;
}

void assertEmpty(const CharStack& stack) {
    assert(stack.isEmpty());
    assert(stack.size() == 0);
}

void assertNotEmpty(const CharStack& stack, int count) {
    assert(!stack.isEmpty());
    assert(stack.size() == count);
}
