#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include "console.h"
#include "vector.h"

using namespace std;

template <typename ValueType>
void sort(Vector<ValueType>& values);

template <typename ValueType>
void buildHeap(Vector<ValueType>& heap);

template <typename ValueType>
void maxHeapify(Vector<ValueType>& heap, int nodeIdx, int size);

int main() {
    Vector<int> values = { 14, 13, 12, 7, 8, 9, 20, 19 };
    sort(values);

    for (int i = 0; i < values.size(); i++) {
        cout << values[i];
        if (i < values.size() - 1) {
            cout << ", ";
        }
    }

    return 0;
}

template <typename ValueType>
void sort(Vector<ValueType>& values) {
    buildHeap(values);

    int n = values.size() - 1;
    while (n > 0) {
        swap(values[0], values[n]);
        n--;
        maxHeapify(values, 0, n);
    }
}

template <typename ValueType>
void buildHeap(Vector<ValueType>& heap) {
    int n = heap.size();
    int lastParent = (n - 1) / 2;

    for (int i = lastParent; i >= 0; i--) {
        maxHeapify(heap, i, n);
    }
}

template <typename ValueType>
void maxHeapify(Vector<ValueType>& heap, int nodeIdx, int size) {
    int leftIdx = 2 * nodeIdx + 1;
    int rightIdx = 2 * nodeIdx + 2;
    int maxIdx = nodeIdx;

    if (leftIdx < size && heap[nodeIdx] < heap[leftIdx]) {
        maxIdx = leftIdx;
    }

    if (rightIdx < size && heap[rightIdx] > heap[maxIdx]) {
        maxIdx = rightIdx;
    }

    if (maxIdx != nodeIdx) {
        swap(heap[nodeIdx], heap[maxIdx]);
        maxHeapify(heap, maxIdx, size);
    }
}
