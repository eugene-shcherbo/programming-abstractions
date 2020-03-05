#include <iostream>

using namespace std;

constexpr int sentitel = 0;

int askToEnterValue() {
    int val;
    cout << "Enter a value or " << sentitel << " to stop entering: ";
    cin >> val;
    return val;
}

int main()
{
    bool isFirstValueRead = false;
    int maxValue = 0;

    while (true) {
        int value = askToEnterValue();

        if (value == sentitel) {
            break;
        } else if (!isFirstValueRead) {
            maxValue = value;
            isFirstValueRead = true;
        } else if (value > maxValue) {
            maxValue = value;
        }
    }

    if (isFirstValueRead) {
        cout << "The largest value you have typed is " << maxValue << endl;
    }

    return 0;
}
