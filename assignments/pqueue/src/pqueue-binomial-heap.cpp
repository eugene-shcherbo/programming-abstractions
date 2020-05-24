#include "pqueue-binomial-heap.h"
using namespace std;

BinomialHeapPQueue::BinomialHeapPQueue() {}

BinomialHeapPQueue::~BinomialHeapPQueue() {
    for (int i = heap_.size() - 1; i >= 0; i--) {
        if (heap_[i] != nullptr) {
            clear(heap_[i]);
        }
        heap_.removeBack();
    }
}

void BinomialHeapPQueue::clear(Node* tree) {
    for (Node* child: tree->children) {
        clear(child);
    }
    delete tree;
}

const string& BinomialHeapPQueue::peek() const {
    if (isEmpty()) {
        throw "error: attepmting to peek from the empty queue";
    }

    return heap_[findMinIndex()]->elem;
}

string BinomialHeapPQueue::extractMin() {
    int minIndex = findMinIndex();
    Node* minHeap = heap_[minIndex];
    string res = minHeap->elem;
    heap_[minIndex] = nullptr;

    Vector<Node*> remainingHeap = minHeap->children;
    Node* carry = nullptr;

    for (int i = 0; i < remainingHeap.size(); i++) {
        if (heap_[i] == nullptr && carry == nullptr) {
            heap_[i] = remainingHeap[i];
        } else if (heap_[i] == nullptr  && carry != nullptr) {
            carry = mergeTrees(remainingHeap[i], carry);
            heap_[i] = nullptr;
        } else if (heap_[i] != nullptr && carry == nullptr) {
            carry = mergeTrees(heap_[i], remainingHeap[i]);
            heap_[i] = nullptr;
        } else {
            Node* tmp = mergeTrees(heap_[i], remainingHeap[i]);
            heap_[i] = carry;
            carry = tmp;
        }
    }

    heap_[minIndex] = carry;
    delete minHeap;
    logSize--;

    return res;
}

int BinomialHeapPQueue::findMinIndex() const {
    int minIndex = 0;

    for (int i = 0; i < heap_.size(); i++) {
        if (heap_[minIndex] == nullptr) {
            minIndex = i;
        }

        if (heap_[i] != nullptr && heap_[i]->elem < heap_[minIndex]->elem) {
            minIndex = i;
        }
    }

    return minIndex;
}

void BinomialHeapPQueue::enqueue(const string& elem) {
    Node* addend = new Node { elem, Vector<Node*>() };

    int i = 0;
    while (i < heap_.size()) {
        if (heap_[i] != nullptr) {
            addend = mergeTrees(heap_[i], addend);
            heap_[i] = nullptr;
        } else {
            break;
        }
        i++;
    }

    if (i == heap_.size()) {
        heap_.add(addend);
    } else {
        heap_[i] = addend;
    }

    logSize++;
}

void BinomialHeapPQueue::mergeHeaps(Vector<Node*>& one, Vector<Node*>& two, Vector<Node*>& res) {
    Node* carry = nullptr;
    int order = 0;

    while (order < one.size() || order < two.size()) {
        if (order >= one.size()) {
            if (carry == nullptr) {
                res.add(two[order]);
            } else {
                carry = mergeTrees(two[order], carry);
                res.add(nullptr);
            }
        } else if (order >= two.size()) {
            if (carry == nullptr) {
                res.add(one[order]);
            } else {
                carry = mergeTrees(one[order], carry);
                res.add(nullptr);
            }
        } else if (one[order] == nullptr && two[order] == nullptr) {
            res.add(carry);
            carry = nullptr;
        } else if (one[order] == nullptr && two[order] != nullptr) {
            carry = mergeTrees(two[order], carry);
            res.add(carry);
            carry = nullptr;
        } else if (one[order] != nullptr && two[order] == nullptr) {
            carry = mergeTrees(one[order], carry);
            res.add(carry);
            carry = nullptr;
        } else {
            Node* tmp = mergeTrees(one[order], two[order]);
            res.add(carry);
            carry = tmp;
        }
        order++;
    }

    if (carry != nullptr) {
        res.add(carry);
    }
}

BinomialHeapPQueue* BinomialHeapPQueue::merge(BinomialHeapPQueue* one, BinomialHeapPQueue* two) {
    BinomialHeapPQueue* res = new BinomialHeapPQueue();
    res->logSize = one->logSize + two->logSize;
    mergeHeaps(one->heap_, two->heap_, res->heap_);
    return res;
}

BinomialHeapPQueue::Node* BinomialHeapPQueue::mergeTrees(Node* lTree, Node* rTree) {
    if (lTree == nullptr) {
        return rTree;
    } else if (rTree == nullptr) {
        return lTree;
    } else if (lTree->elem < rTree->elem) {
        lTree->children.add(rTree);
        return lTree;
    } else {
        rTree->children.add(lTree);
        return rTree;
    }
}
