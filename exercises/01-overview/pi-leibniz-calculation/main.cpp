#include <iostream>

using namespace std;

double calculatePI();

int main()
{
    cout << "This program calculates approximate value of PI." << endl;
    cout << "PI is equal to " << calculatePI() << endl;

    return 0;
}

double calculatePI() {
    constexpr int TERMS{1000};
    double series{0};

    for (int i{0}, term{1}; i < TERMS / 2; i++, term += 4) {
        series = series + 1.0/term - 1.0/(term + 2);
    }

    return series * 4;
}
