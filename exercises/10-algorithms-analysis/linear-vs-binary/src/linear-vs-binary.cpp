#include <iostream>
#include <iomanip>
#include <chrono>
#include "vector.h"
#include "console.h"

using namespace std;

typedef int (*SearchAlgorithm)(const Vector<int>&, int, int&);

int linearSearch(const Vector<int>& values, int value, int& numOfComparisons);
int binarySearch(const Vector<int>& values, int value, int& numOfComparisons);

void searchPerformanceReport();
Vector<int>* randomSortedSequence(size_t size, int from, int to);

double runTrials(int trialsNum, size_t problemSize, SearchAlgorithm algorithm);

int main() {
    searchPerformanceReport();
    return 0;
}

void searchPerformanceReport() {
    Vector<size_t> sequenceSizes = { 10, 50, 100, 1000, 5000, 10000, 50000, 100000 };

    cout << "    N    |   Linear   |   Binary   " << endl;
    cout << "---------+------------+------------" << endl;

    for (size_t size : sequenceSizes) {
        Vector<int>* random = randomSortedSequence(size, SHRT_MIN, SHRT_MAX);

        double linearComparisons = runTrials(20, size, linearSearch);
        double binaryComparisons = runTrials(20, size, binarySearch);

        cout << setw(7) << size << "  |";
        cout << setw(9) << fixed << setprecision(1) << linearComparisons << "   |";
        cout << setw(8) << binaryComparisons << endl;

        delete random;
    }
}

int linearSearch(const Vector<int>& values, int valueToSearch, int& numOfComparisons) {
    for (int i = 0; i < values.size(); i++) {
        numOfComparisons++;
        if (values[i] == valueToSearch) {
            return i;
        }
    }

    return -1;
}

int binarySearchHelper(const Vector<int>& values, int valueToSearch, int& numOfComparisons, int start, int end) {
    if (start > end) return -1;

    int mid = (start + end) / 2;
    numOfComparisons++;

    if (values[mid] == valueToSearch) {
        return mid;
    } else if (values[mid] < valueToSearch) {
        return binarySearchHelper(values, valueToSearch, numOfComparisons, mid + 1, end);
    } else {
        return binarySearchHelper(values, valueToSearch, numOfComparisons, start, mid - 1);
    }
}

int binarySearch(const Vector<int>& values, int valueToSearch, int& numOfComparisons) {
    return binarySearchHelper(values, valueToSearch, numOfComparisons, 0, values.size() - 1);
}

Vector<int>* randomSortedSequence(size_t size, int from, int to) {
    auto values = new Vector<int>(size);

    for (size_t i = 0; i < size; i++) {
        values->set(i, randomInteger(from, to));
    }

    sort(values->begin(), values->end());
    return values;
}

double runTrials(int trialsNum, size_t problemSize, SearchAlgorithm algorithm) {
    int numOfComparisons = 0;

    for (int i = 0; i < trialsNum; i++) {
        Vector<int>* randomValues = randomSortedSequence(problemSize, SHRT_MIN, SHRT_MAX);
        int randomKeyToSearch = randomInteger(SHRT_MIN, SHRT_MAX);
        algorithm(*randomValues, randomKeyToSearch, numOfComparisons);
        delete randomValues;
    }

    return (double)numOfComparisons / trialsNum;
}

