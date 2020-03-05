#include <iostream>
#include "console.h"

using namespace std;

int fibonacci(int n);
void testFibonacci(int n, int expected);

int main() {
    testFibonacci(0, 0);
    testFibonacci(1, 1);
    testFibonacci(2, 2);
    testFibonacci(5, 8);

    return 0;
}

void testFibonacci(int n, int expected) {
    int actual = fibonacci(n);
    cout << "fib(" << n << ") is " << actual << endl;
    cout << "result: " << (actual == expected ? "success." : "failed.")
         << endl << endl;
}

int fibonacci(int n) {
    int first = 0;
    int second = 1;
    int res = 0;
    for (int i = 0; i < n; ++i) {
        res = first + second;
        first = second;
        second = res;
    }

    return res;
}
