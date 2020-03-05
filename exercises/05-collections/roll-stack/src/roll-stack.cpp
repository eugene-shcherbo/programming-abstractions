#include <iostream>
#include "stack.h"
#include "queue.h"
#include "console.h"

using namespace std;

void roll(Stack<char>& stack, int n, int k);
void testRoll(const Stack<char>& stack, int n, int k, const Stack<char>& expected);
void getStack(Stack<char>& stack, char c1, char c2, char c3, char c4);

int main() {
    Stack<char> values;
    Stack<char> expected;

    getStack(values, 'A', 'B', 'C', 'D');
    getStack(expected, 'D', 'A', 'B', 'C');
    testRoll(values, 4, 1, expected);

    getStack(expected, 'A', 'C', 'D', 'B');
    testRoll(values, 3, 2, expected);

    testRoll(values, 2, 4, values);
    // testRoll(values, 5, 4, values);

    return 0;
}

void getStack(Stack<char>& stack, char c1, char c2, char c3, char c4) {
    stack.clear();
    stack.push(c1);
    stack.push(c2);
    stack.push(c3);
    stack.push(c4);
}

void testRoll(const Stack<char>& stack, int n, int k, const Stack<char>& expected) {
    Stack<char> actual = stack;
    roll(actual, n, k);

    cout << "Stack " << stack << " after roll is " << actual << endl;
    cout << "Result: " << (actual == expected ? "Success." : "Failed.") << endl << endl;
}

void roll(Stack<char>& stack, int n, int k) {
    if (n < 0 || k < 0 || n > stack.size()) {
        error("roll: argument out of range");
    }

    Vector<char> rolled(n);

    for (int i = 0; i < n; ++i) {
        int index = (n - i - 1 + k) % n;
        rolled[index] = stack.pop();
    }

    for (char el: rolled) {
        stack.push(el);
    }
}
