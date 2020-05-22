#include "pqueue-vector.h"

using namespace std;

VectorPQueue::VectorPQueue() {}
VectorPQueue::~VectorPQueue() {}

const string& VectorPQueue::peek() const {
    if (isEmpty()) {
        throw "attempt to peek from the empty queue";
    }

    return items_[findMinIndex()];
}

string VectorPQueue::extractMin() {
    if (isEmpty()) {
        throw "attempt to dequeue from the empty queue";
    }
    int index = findMinIndex();
    string el = items_[index];
    items_.remove(index);
    logSize--;
    return el;
}

void VectorPQueue::enqueue(const string& elem) {
    items_.add(elem);
    logSize++;
}

VectorPQueue* VectorPQueue::merge(VectorPQueue* one, VectorPQueue* two) {
    VectorPQueue* res = new VectorPQueue();

    if (one != nullptr) {
        for (int i = 0; i < one->size(); i++) {
            res->enqueue(one->items_[i]);
        }
    }

    if (two != nullptr) {
        for (int i = 0; i < two->size(); i++) {
            res->enqueue(two->items_[i]);
        }
    }

    return res;
}

int VectorPQueue::findMinIndex() const {
    int minIndex = 0;

    for (int i = 1; i < size(); i++) {
        if (items_[i] < items_[minIndex]) {
            minIndex = i;
        }
    }

    return minIndex;
}
