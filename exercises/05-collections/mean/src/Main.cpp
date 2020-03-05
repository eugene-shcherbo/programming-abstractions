#include <iostream>
#include "vector.h"
#include "console.h"
using namespace std;

double mean(const Vector<double>& data);
void testMean(const Vector<double>& data, double expected);

int main() {
    testMean(Vector<double> { 1.0, 2.0, 3.0 }, 2.0);
    testMean(Vector<double> { 5.8, 7.13, 9.2, 1.02, 3.11 }, 5.252);
    testMean(Vector<double>(), 0);

    return 0;
}

void testMean(const Vector<double>& data, double expected) {
    double actual = mean(data);

    cout << "Distribution " << data.toString() << " has mean equal to " << actual << endl
         << "RESULT is " << (actual == expected ? "SUCCESS" : "FAILED") << endl;
}

double mean(const Vector<double>& data) {
    auto n = data.size();

    if (n == 0) {
        return .0;
    }

    double sum = .0;
    for (double el: data) {
        sum += el;
    }

    return sum / n;
}
