#ifndef _queue_h_
#define _queue_h_

#include "error.h"

namespace collections {

    template <typename ValueType>
    class PriorityQueue {

    public:
        PriorityQueue();
        ~PriorityQueue();

        bool isEmpty() const;
        int size() const;
        void enqueue(ValueType val, double priority);
        ValueType dequeue();
        ValueType peek() const;
        void clear();
        void reverse();

    private:
        struct Cell {
            ValueType val;
            Cell* link;
            double priority;
        };

        PriorityQueue(const PriorityQueue& other);

        Cell* head_;
        int count_;

        PriorityQueue& operator=(const PriorityQueue& other);
    };

    template <typename ValueType>
    PriorityQueue<ValueType>::PriorityQueue() {
        head_ = nullptr;
        count_ = 0;
    }

    template <typename ValueType>
    PriorityQueue<ValueType>::~PriorityQueue() {
        clear();
    }

    template <typename ValueType>
    bool PriorityQueue<ValueType>::isEmpty() const {
        return count_ == 0;
    }

    template <typename ValueType>
    int PriorityQueue<ValueType>::size() const {
        return count_;
    }

    template <typename ValueType>
    void PriorityQueue<ValueType>::clear() {
        while (!isEmpty()) {
            dequeue();
        }
    }

    template <typename ValueType>
    void PriorityQueue<ValueType>::enqueue(ValueType val, double priority) {
        Cell* cell = new Cell { val, nullptr, priority };

        if (isEmpty()) {
            head_ = cell;
        } else if (head_->priority > priority) {
            cell->link = head_;
            head_ = cell;
        } else {
            Cell* prev = head_;

            while (prev->link != nullptr && prev->link->priority <= priority) {
                prev = prev->link;
            }

            cell->link = prev->link;
            prev->link = cell;
        }

        count_++;
    }

    template <typename ValueType>
    ValueType PriorityQueue<ValueType>::dequeue() {
        if (isEmpty()) {
            error("dequeue: Attempting dequeue from an empty queue");
        }
        Cell* dequeud = head_;
        ValueType result = head_->val;
        head_ = head_->link;
        delete dequeud;
        count_--;
        return result;
    }

    template <typename ValueType>
    ValueType PriorityQueue<ValueType>::peek() const {
        if (isEmpty()) {
            error("dequeue: Attempting dequeue from an empty queue");
        }
        return head_->val;
    }

    template <typename ValueType>
    void PriorityQueue<ValueType>::reverse() {
        Cell* next;
        Cell* prev = nullptr;
        Cell* current = head_;

        while (current != nullptr) {
            next = current->link;
            current->link = prev;
            prev = current;
            current = next;
        }
        head_ = prev;
    }

}


#endif
