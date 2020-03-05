#include <iostream>

using namespace std;

bool isPerfect(int n);

int main()
{
    cout << "This programs display all perfect numbers in the range 1 to 9999." << endl
         << " Pefrect numbers: ";

    for (int i = 1; i <= 9999; ++i) {
        if (isPerfect(i)) {
            cout << i << " ";
        }
    }

    cout << endl;

    return 0;
}

bool isPerfect(int n) {
    int divisorsSum = 0;
    for (int i = 1; i < n; ++i) {
        if (n % i == 0) {
            divisorsSum += i;
        }
    }
    return n == divisorsSum;
}
