#include <iostream>

using namespace std;

void generateHeilstoneSequence(int number);

int main()
{
    int number;
    cout << "The program displays Heilstone sequence. " << endl
         << "Enter a number to start generate: ";
    cin >> number;

    generateHeilstoneSequence(number);

    return 0;
}

void generateHeilstoneSequence(int number) {
    while (number != 1) {
        int origin = number;

        if (number % 2 == 0) {
            number /= 2;
            cout << origin << " is even, so I divide it by 2 to get " << number;
        } else {
            number = number * 3 + 1;
            cout << origin << " is odd, so I multiply by 3 and add 1 to get " << number;
        }

        cout << endl;
    }
}
