#ifndef _priority_queue_h_
#define _priority_queue_h_

#include "vector.h"

namespace collections {

    template <typename ValueType>
    void swap(ValueType& val1, ValueType& val2);

    template <typename ValueType>
    class PriorityQueue {
    public:
        PriorityQueue();

        ValueType dequeue();
        const ValueType& peek() const;
        void enqueue(const ValueType& val, double priority);
        bool isEmpty() const;

    private:
        struct HeapNode {
            ValueType val;
            double priority;
        };

        Vector<HeapNode> nodes_;

        int findParentIndex(int n) const;
        int findLeftChildIndex(int n) const;
        int findRightChildIndex(int n) const;
        int minIndex(int node1Idx, int node2Idx) const;
    };

    template <typename ValueType>
    PriorityQueue<ValueType>::PriorityQueue() {
    }

    template <typename ValueType>
    void PriorityQueue<ValueType>::enqueue(const ValueType& val, double priority) {
        HeapNode node { val, priority };
        nodes_.add(node);

        int currIndex = nodes_.size() - 1;

        while (currIndex > 0) {
            int parentIdx = findParentIndex(currIndex);
            HeapNode& parent = nodes_[parentIdx];

            if (parent.priority <= priority) {
                break;
            } else {
                swap(parent, nodes_[currIndex]);
            }

            currIndex = parentIdx;
        }
    }

    template <typename ValueType>
    const ValueType& PriorityQueue<ValueType>::peek() const {
        if (isEmpty()) {
            throw "error: attempting to peek from the empty queue";
        }

        return nodes_[0].val;
    }

    template <typename ValueType>
    ValueType PriorityQueue<ValueType>::dequeue() {
        if (isEmpty()) {
            throw "error: attempting to dequeue from the empty queue";
        } else if (nodes_.size() == 1) {
            return nodes_.removeBack().val;
        } else {
            ValueType res = nodes_[0].val;
            nodes_[0] = nodes_.removeBack();

            int currIndex = 0;
            int height = log2(nodes_.size());

            while (currIndex < pow(2, height) - 1) {
                int leftChildIdx = findLeftChildIndex(currIndex);
                int rightChildIdx = findRightChildIndex(currIndex);
                int minIdx = minIndex(leftChildIdx, rightChildIdx);

                if (nodes_[currIndex].priority <= nodes_[minIdx].priority) {
                    break;
                } else {
                    swap(nodes_[currIndex], nodes_[minIdx]);
                }

                currIndex = minIdx;
            }

            return res;
        }
    }

    template <typename ValueType>
    bool PriorityQueue<ValueType>::isEmpty() const {
        return nodes_.isEmpty();
    }

    template <typename ValueType>
    int PriorityQueue<ValueType>::findParentIndex(int n) const {
        return (n - 1) / 2;
    }

    template <typename ValueType>
    int PriorityQueue<ValueType>::findLeftChildIndex(int n) const {
        return (n * 2) + 1;
    }

    template <typename ValueType>
    int PriorityQueue<ValueType>::findRightChildIndex(int n) const {
        return (n * 2) + 2;
    }

    template <typename ValueType>
    int PriorityQueue<ValueType>::minIndex(int node1Idx, int node2Idx) const {
        if (node2Idx > nodes_.size() - 1) {
            return node1Idx;
        } else {
            return nodes_[node1Idx].priority < nodes_[node2Idx].priority
                ? node1Idx
                : node2Idx;
        }
    }

    template <typename ValueType>
    void swap(ValueType& val1, ValueType& val2) {
        ValueType tmp = val1;
        val1 = val2;
        val2 = tmp;
    }

}

#endif
