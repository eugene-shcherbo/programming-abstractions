#include <iostream>

using namespace std;

constexpr int SENTITEL = 0;

int main()
{
    int numberInputs = 0;
    int largestValue = 0;
    int preLargestValue = 0;

    while (true) {
        int value;
        cout << "Enter a value or " << SENTITEL << " to finish: ";
        cin >> value;

        if (value == SENTITEL) {
            break;
        } else if (numberInputs == 0) {
            largestValue = preLargestValue = value;
        } else if (value > largestValue) {
            preLargestValue = largestValue;
            largestValue = value;
        } else if (value > preLargestValue) {
            preLargestValue = value;
        }

        ++numberInputs;
    }

    if (numberInputs > 0) {
        cout << "The largest value was " << largestValue << '.' << endl
             << "The second largest value was " << preLargestValue << '.' << endl;
    }

    return 0;
}
