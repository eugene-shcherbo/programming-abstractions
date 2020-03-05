#include <iostream>
using namespace std;

int reverseNumber(int number);

int main()
{
    int number;
    cout << "The program reverses digits of a number." << endl
         << "Type a number: ";
    cin >> number;

    cout << "The reversed integer is " << reverseNumber(number) << endl;

    return 0;
}

int reverseNumber(int number) {
    int revNumber = 0;

    while (number > 0) {
        revNumber = revNumber * 10 + number % 10;
        number /= 10;
    }

    return revNumber;
}
