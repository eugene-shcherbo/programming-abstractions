#include <iostream>
#include <iomanip>
#include <chrono>
#include "vector.h"
#include "console.h"

using namespace std;

void sort(Vector<int>& values);
void sortPerformanceReport();
Vector<int>* randomSequence(size_t size, int from, int to);

int main() {
    sortPerformanceReport();
    return 0;
}


// Our sort algorithms assumes that all the values in the vector
// in the range [0, 9999]
void sort(Vector<int>& values) {
    constexpr int LOW = 0;
    constexpr int HIGHT = 9999;

    Vector<int> hashTable(HIGHT + 1);

    for (int value : values) {
        if (value < LOW && value > HIGHT) error("elements should be in the range [0, 9999]");
        hashTable[value]++;
    }

    int sortedIndex = 0;
    for (int i = 0; i < hashTable.size(); i++) {
        while (hashTable[i] > 0) {
            values[sortedIndex] = i;
            sortedIndex++;
            hashTable[i]--;
        }
    }
}

void sortPerformanceReport() {
    Vector<size_t> sequenceSizes = { 10, 50, 100, 1000, 5000, 10000, 50000, 100000, 500000, 1000000 };

    cout << "    N    |   Time (sec)   " << endl;
    cout << "---------+-----------------" << endl;

    for (size_t size : sequenceSizes) {
        Vector<int>* random = randomSequence(size, 0, 9999);
        auto start = std::chrono::high_resolution_clock::now();
        sort(*random);
        auto finish = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration<double>(finish - start).count();

        cout << setw(7) << size << "  |";
        cout << setw(12) << fixed << setprecision(5) << duration << endl;

        delete random;
    }

}

Vector<int>* randomSequence(size_t size, int from, int to) {
    Vector<int>* sequence = new Vector<int>(size);

    for (int i = 0; i < size; i++) {
        (*sequence)[i] = randomInteger(from, to);
    }

    return sequence;
}


