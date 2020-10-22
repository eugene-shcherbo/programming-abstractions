#include <iostream>
#include <iomanip>
#include <chrono>
#include "vector.h"
#include "console.h"

using namespace std;

static constexpr int CROSSOVER = 22;

typedef int (*Pivot)(const Vector<int>& values, int start, int finish);
typedef void (*QuickSortAlgorithm)(Vector<int>& values, int start, int finish, Pivot pivotSelector);

void quickSortDefault(Vector<int>& values, int start, int finish, Pivot pivotSelector);
void quickSortHybrid(Vector<int>& values, int start, int finish, Pivot pivotSelector);

void sortPerformanceReport();
Vector<int>* randomSequence(size_t size, int from, int to);

double measureRunningTime(Vector<int> values, QuickSortAlgorithm algorithm);

void quickSort(Vector<int>& values, QuickSortAlgorithm algorithm);
void insertionSort(Vector<int>& values, int start, int finish);
void selectionSort(Vector<int>& values, int start, int finish);

int main() {
    sortPerformanceReport();
    return 0;
}

void sortPerformanceReport() {
    Vector<size_t> sequenceSizes = { 10, 50, 100, 1000, 5000, 10000, 50000, 100000, 500000, 1000000 };

    cout << "    N    |   QSort1   |   QSort2   " << endl;
    cout << "---------+------------+------------" << endl;

    for (size_t size : sequenceSizes) {
        Vector<int>* random = randomSequence(size, SHRT_MIN, SHRT_MAX);

        double defaultQuickSort = measureRunningTime(*random, quickSortDefault);
        double hybrid = measureRunningTime(*random, quickSortHybrid);

        cout << setw(7) << size << "  |";
        cout << setw(9) << fixed << setprecision(3) << defaultQuickSort << "   |";
        cout << setw(8) << hybrid << endl;

        delete random;
    }
}


void selectionSort(Vector<int>& values, int start, int finish) {
    for (int i = start; i < finish; i++) {
        int min = i;
        for (int j = i + 1; j <= finish; j++) {
            if (values[j] < values[min]) {
                min = j;
            }
        }
        swap(values[i], values[min]);
    }
}

void insertionSort(Vector<int>& values, int start, int finish) {
    for (int i = start + 1; i <= finish; i++) {
        for (int j = i; j > start && values[j] < values[j - 1]; j--)
            swap(values[j], values[j - 1]);
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

int medianElementPivot(const Vector<int>& values, int start, int finish) {
    return medianOf(values, start, (start + finish) / 2, finish);
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

void quickSort(Vector<int>& values, QuickSortAlgorithm algorithm) {
    algorithm(values, 0, values.size() - 1, medianElementPivot);
}

void quickSortDefault(Vector<int>& values, int start, int finish, Pivot pivotSelector) {
    if (start >= finish) return;
    int boundary = partition(values, start, finish, pivotSelector);
    quickSortDefault(values, start, boundary - 1, pivotSelector);
    quickSortDefault(values, boundary + 1, finish, pivotSelector);
}

void quickSortHybrid(Vector<int>& values, int start, int finish, Pivot pivotSelector) {
    if ((finish - start + 1) <= CROSSOVER) {
        insertionSort(values, start, finish);
    } else {
        int boundary = partition(values, start, finish, pivotSelector);
        quickSortHybrid(values, start, boundary - 1, pivotSelector);
        quickSortHybrid(values, boundary + 1, finish, pivotSelector);
    }
}

double measureRunningTime(Vector<int> values, QuickSortAlgorithm algorithm) {
    auto start = std::chrono::high_resolution_clock::now();
    quickSort(values, algorithm);
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
