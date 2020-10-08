#include <iostream>
#include <iomanip>
#include <chrono>
#include "vector.h"
#include "console.h"

using namespace std;

void sort(Vector<int>& values);
void sortPerformanceReport();
Vector<int>* randomSequence(size_t size);
Vector<int>* randomSortedSequence(size_t size);

int main() {
    sortPerformanceReport();

    return 0;
}

void sort(Vector<int>& values) {
    for (int i = 1; i < values.size(); i++) {
        for (int j = i; j > 0 && values[j - 1] > values[j]; j--) {
            swap(values[j - 1], values[j]);
        }
    }
}

void sortPerformanceReport() {
    Vector<size_t> sequenceSizes = { 10, 50, 100, 1000, 5000, 10000, 50000,
                                    /* too long in the worst case 100000 */ };

    cout << "    N    |   Time (sec)   " << endl;
    cout << "---------+-----------------" << endl;

    for (size_t size : sequenceSizes) {
        Vector<int>* random = randomSequence(size);
        auto start = std::chrono::high_resolution_clock::now();
        sort(*random);
        auto finish = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration<double>(finish - start).count();

        cout << setw(7) << size << "  |";
        cout << setw(12) << fixed << setprecision(5) << duration << endl;

        delete random;
    }

}

Vector<int>* randomSequence(size_t size) {
    Vector<int>* sequence = new Vector<int>(size);

    for (int i = 0; i < size; i++) {
        (*sequence)[i] = randomInteger(0, INT_MAX);
    }

    return sequence;
}

Vector<int>* randomSortedSequence(size_t size) {
    Vector<int>* sequence = new Vector<int>(size);

    for (int i = 0; i < size; i++) {
        (*sequence)[i] = randomInteger(0, INT_MAX);
    }

    sequence->sort();
    return sequence;
}


