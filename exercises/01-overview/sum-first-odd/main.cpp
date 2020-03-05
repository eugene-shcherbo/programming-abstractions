#include <iostream>

using namespace std;

int calculateSumOfFirstOdd(int n);

int main()
{
    int numberToSum;
    cout << "Enter how many odd numbers you want to sum: ";
    cin >> numberToSum;

    cout << "Sum is " << calculateSumOfFirstOdd(numberToSum) << endl;

    return 0;
}

int calculateSumOfFirstOdd(int n) {
    int firstMember = 1;
    int step = 2;
    int lastMember = firstMember + (n - 1) * step;

    return n * (firstMember + lastMember) / 2;
}
