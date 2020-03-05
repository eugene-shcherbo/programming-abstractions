#include <iostream>

using namespace std;

int main()
{
    int number;
    cout << "This program displays prime factorization of a number." << endl
         << " Enter a number: ";
    cin >> number;

    for (int i = 2; i <= number; ++i) {
        while (number % i == 0) {
            cout << i;

            if (number != i) {
                cout << " x ";
            }

            number /= i;
        }
    }

    cout << endl;

    return 0;
}
