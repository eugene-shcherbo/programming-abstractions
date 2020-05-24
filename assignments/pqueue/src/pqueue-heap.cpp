#include <cmath>
#include "pqueue-heap.h"
using namespace std;

int parentIndex(int index);

HeapPQueue::HeapPQueue() {
    capacity_ = 10;
    logSize = 0;
    elements_ = new string[capacity_];
}

HeapPQueue::~HeapPQueue() {
    delete[] elements_;
}

const string& HeapPQueue::peek() const {
    if (isEmpty()) {
        throw "error: attemptint to peek from the empty queue";
    }
    return elements_[0];
}

string HeapPQueue::extractMin() {
    if (isEmpty()) {
        throw "error: attemptint to extract from the empty queue";
    }

    std::string res = elements_[0];
    elements_[0] = elements_[logSize - 1];
    minHeapify(0);
    logSize--;
    return res;
}

void HeapPQueue::enqueue(const string& el) {
    add(el);
    int current = logSize;

    while (current > 0) {
        int parent = parentIndex(current);

        if (*(elements_ + parent) > *(elements_ + current)) {
            swap(*(elements_ + parent), *(elements_ + current));
            current = parent;
        } else {
            break;
        }
    }

    logSize++;
}

HeapPQueue* HeapPQueue::merge(HeapPQueue* one, HeapPQueue* two) {
    HeapPQueue* res = new HeapPQueue();

    if (one != nullptr) {
        for (int i = 0; i < one->logSize; i++) {
            res->add(one->elements_[i]);
            res->logSize++;
        }
    }

    if (two != nullptr) {
        for (int i = 0; i < two->logSize; i++) {
            res->add(two->elements_[i]);
            res->logSize++;
        }
    }

    for (int parent = parentIndex(res->logSize - 1); parent >= 0; parent--) {
        res->minHeapify(parent);
    }

    return res;
}


void HeapPQueue::minHeapify(int index) {
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    int min = index;

    if (left < logSize && *(elements_ + left) < *(elements_ + index)) {
        min = left;
    }

    if (right < logSize && *(elements_ + right) < *(elements_ + min)) {
        min = right;
    }

    if (min != index) {
        swap(*(elements_ + min), *(elements_ + index));
        minHeapify(min);
    }
}

void HeapPQueue::extendCapacity() {
    capacity_ *= 2;
    std::string* old = elements_;
    elements_ = new string[capacity_];

    for (int i = 0; i < logSize; i++) {
        elements_[i] = old[i];
    }

    delete[] old;
}

int parentIndex(int index) {
    return (index - 1) / 2;
}


void HeapPQueue::add(std::string el) {
    if (size() == capacity_) {
        extendCapacity();
    }
    elements_[logSize] = el;
}
