#include <iostream>
#include <iomanip>
#include <chrono>
#include "vector.h"
#include "console.h"

using namespace std;

typedef void (*SortAlgorithm)(Vector<int>& values);
typedef int (*Pivot)(const Vector<int>& values, int start, int finish);

void quickSortFirstPivot(Vector<int>& values);
void quickSortMedian(Vector<int>& values);

void sortPerformanceReport();
Vector<int>* randomSequence(size_t size, int from, int to);

double measureRunningTime(SortAlgorithm sort, Vector<int> values);

void quickSort(Vector<int>& values, int start, int finish, Pivot pivotSelector);

int main() {
    sortPerformanceReport();
    return 0;
}

void sortPerformanceReport() {
    Vector<size_t> sequenceSizes = { 10, 50, 100, 1000, 5000, 10000, 50000, 100000, 500000 };

    cout << "    N    |   QSort1   |   QSort2   " << endl;
    cout << "---------+------------+------------" << endl;

    for (size_t size : sequenceSizes) {
        Vector<int>* random = randomSequence(size, SHRT_MIN, SHRT_MAX);

        double firstPivot = measureRunningTime(quickSortFirstPivot, *random);
        double medianPivot = measureRunningTime(quickSortMedian, *random);

        cout << setw(7) << size << "  |";
        cout << setw(9) << fixed << setprecision(3) << firstPivot << "   |";
        cout << setw(8) << medianPivot << endl;

        delete random;
    }
}

int medianOf(const Vector<int>& values, int i1, int i2, int i3) {
    int one = values[i1];
    int two = values[i2];
    int three = values[i3];

    if (one < two) {
        if (one >= three) {
            return i1;
        } else {
            return two < three ? i2 : i3;
        }
    } else {
        if (one < three) {
            return i1;
        } else {
            return two >= three ? i2 : i3;
        }
    }
}

int firstElementPivot(const Vector<int>& values, int start, int finish) {
    return start;
}

int medianElementPivot(const Vector<int>& values, int start, int finish) {
    return medianOf(values, start, (start + finish) / 2, finish);
}

void quickSortFirstPivot(Vector<int>& values) {
    quickSort(
        values,
        0,
        values.size() - 1,
        firstElementPivot);
}

void quickSortMedian(Vector<int>& values) {
    quickSort(
        values,
        0,
        values.size() - 1,
        medianElementPivot);
}

int partition(Vector<int>& values, int start, int finish, Pivot pivotSelector) {
    int pivotIndex = pivotSelector(values, start, finish);
    int pivot = values[pivotIndex];
    swap(values[start], values[pivotIndex]);

    int lh = start + 1;
    int rh = finish;

    while (true) {
        while (lh < rh && values[rh] >= pivot) rh--;
        while (lh < rh && values[lh] < pivot) lh++;
        if (lh == rh) break;
        swap(values[lh], values[rh]);
    }

    if (values[lh] >= pivot) return start;
    values[start] = values[lh];
    values[lh] = pivot;
    return lh;
}

void quickSort(Vector<int>& values, int start, int finish, Pivot pivotSelector) {
    if (start >= finish) return;
    int boundary = partition(values, start, finish, pivotSelector);
    quickSort(values, start, boundary - 1, pivotSelector);
    quickSort(values, boundary + 1, finish, pivotSelector);
}

double measureRunningTime(SortAlgorithm sort, Vector<int> values) {
    auto start = std::chrono::high_resolution_clock::now();
    sort(values);
    auto finish = std::chrono::high_resolution_clock::now();
    return std::chrono::duration<double>(finish - start).count();
}

Vector<int>* randomSequence(size_t size, int from, int to) {
    auto values = new Vector<int>(size);

    for (size_t i = 0; i < size; i++) {
        values->set(i, randomInteger(from, to));
    }

    return values;
}
