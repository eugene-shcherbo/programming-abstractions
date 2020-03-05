#include <iostream>

using namespace std;

int calculateSumFirst(int n);

int main()
{
    cout << "Gauss's sum is " << calculateSumFirst(100) << endl;

    return 0;
}

int calculateSumFirst(int n) {
    return n * (n + 1) / 2;
}
