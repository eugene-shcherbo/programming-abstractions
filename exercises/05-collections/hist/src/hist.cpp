#include <iostream>
#include <iomanip>
#include "hist.h"

void printRange(int range);

void printDataInRange(int n, char dataIndicator);

int countDataInRange(const Vector<int>& data, int from, int to);

void printHistogram(const Vector<int>& data, int min, int max, int rangeSize, char dataIndicator) {
    for (int i = min; i <= max; i += rangeSize) {
        printRange(i);
        printDataInRange(countDataInRange(data, i, i + rangeSize), dataIndicator);
    }
}

void printRange(int range) {
   std::cout << std::setw(2) << std::setfill('0') << range << "s:";
}

void printDataInRange(int n, char dataIndicator) {
    for (int i = 0; i < n; ++i) {
        std::cout << dataIndicator;
    }
    std::cout << std::endl;
}

int countDataInRange(const Vector<int>& data, int from, int to) {
    int res = 0;

    for (int el: data) {
        if (el >= from && el < to) {
            ++res;
        }
    }

    return res;
}
