#ifndef _queue_h_
#define _queue_h

#include "error.h"

namespace collections {

    template <typename ValueType>
    class Queue {
    public:
        Queue();
        ~Queue();

        bool isEmpty() const;
        int size() const;
        void enqueue(ValueType val);
        ValueType dequeue();
        ValueType peek() const;


    private:
        static constexpr int INITIAL_CAPACITY = 10;

        Queue(const Queue& other);

        int tail_;
        int head_;
        int capacity_;
        ValueType* values_;

        void expandCapacity();

        Queue& operator= (const Queue& other);
    };

    template <typename ValueType>
    Queue<ValueType>::Queue() {
        tail_ = head_ = 0;
        capacity_ = INITIAL_CAPACITY;
        values_ = new ValueType[capacity_];
    }

    template <typename ValueType>
    Queue<ValueType>::~Queue() {
        delete[] values_;
    }

    template <typename ValueType>
    bool Queue<ValueType>::isEmpty() const {
        return head_ == tail_;
    }

    template <typename ValueType>
    int Queue<ValueType>::size() const {
        return (tail_ + capacity_ - head_) % capacity_;
    }

    template <typename ValueType>
    void Queue<ValueType>::enqueue(ValueType val) {
        if (size() == capacity_ - 1) {
            expandCapacity();
        }
        values_[tail_] = val;
        tail_ = (tail_ + 1) % capacity_;
    }

    template <typename ValueType>
    ValueType Queue<ValueType>::dequeue() {
        if (isEmpty()) {
            error("dequeue: Attempting to dequeue an empty queue");
        }
        ValueType val = values_[head_];
        head_ = (head_ + 1) % capacity_;
        return val;
    }

    template <typename ValueType>
    ValueType Queue<ValueType>::peek() const {
        if (isEmpty()) {
            error("dequeue: Attempting to dequeue an empty queue");
        }
        return values_[head_];
    }

    template <typename ValueType>
    void Queue<ValueType>::expandCapacity() {
        int count = size();
        ValueType* oldValues = values_;
        values_ = new ValueType[capacity_ * 2];
        for (int i = 0; i < count; i++) {
            values_[i] = oldValues[(i + head_) % capacity_];
        }
        capacity_ *= 2;
        tail_ = count;
        head_ = 0;
        delete[] oldValues;
    }

}

#endif
