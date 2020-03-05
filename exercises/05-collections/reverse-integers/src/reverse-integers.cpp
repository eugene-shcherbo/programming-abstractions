#include <iostream>
#include "simpio.h"
#include "stack.h"
#include "console.h"

using namespace std;

void readValues(Stack<int>& values) {
    cout << "Enter a list of integers, ending with 0: " << endl;

    while (true) {
        int value = getInteger("? ");

        if (value == 0) {
            break;
        }

        values.push(value);
    }
}

void printValues(Stack<int>& values) {
    cout << "Integers in the reverse order are:" << endl;
    while (!values.isEmpty()) {
        cout << values.pop() << endl;
    }
}

int main() {
    Stack<int> values;
    readValues(values);
    printValues(values);

    return 0;
}
