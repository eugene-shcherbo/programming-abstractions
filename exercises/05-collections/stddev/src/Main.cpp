#include <iostream>
#include "console.h"
#include "vector.h"
using namespace std;

double stddev(const Vector<double>& data);
double calcMean(const Vector<double>& data);
void testStddev(const Vector<double>& data, double expected);

int main() {
    testStddev(Vector<double>(), 0);
    testStddev(Vector<double> { 4, 9, 11, 12, 17, 5, 8, 12, 14 }, 3.937787810371);

    return 0;
}

void testStddev(const Vector<double>& data, double expected) {
    double actual = stddev(data);
    cout << "Distribution " << data.toString() << " has the following standard deviation: " << actual << endl
         << "RESULT: " << (actual == expected ? "SUCCESS" : "FAILED") << endl;
}

double stddev(const Vector<double>& data) {
    int n = data.size();

    if (n == 0) {
        return .0;
    }

    double mean = calcMean(data);
    double sum = 0;

    for (double el: data) {
        sum += pow(mean - el, 2);
    }

    return sqrt(sum / n);
}

double calcMean(const Vector<double>& data) {
    int n = data.size();

    if (n == 0) {
        return .0;
    }

    double sum = 0;
    for (double el: data) {
        sum += el;
    }

    return sum / n;
}
