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
        void reverse();


    private:
        static constexpr int INITIAL_CAPACITY = 10;

        Queue(const Queue& other);

        int count_;
        int head_;
        int capacity_;
        ValueType* values_;

        void expandCapacity();
        int tail() const;

        Queue& operator= (const Queue& other);
    };

    template <typename ValueType>
    Queue<ValueType>::Queue() {
        head_ = 0;
        count_ = 0;
        capacity_ = INITIAL_CAPACITY;
        values_ = new ValueType[capacity_];
    }

    template <typename ValueType>
    Queue<ValueType>::~Queue() {
        delete[] values_;
    }

    template <typename ValueType>
    bool Queue<ValueType>::isEmpty() const {
        return count_ == 0;
    }

    template <typename ValueType>
    int Queue<ValueType>::size() const {
        return count_;
    }

    template <typename ValueType>
    void Queue<ValueType>::enqueue(ValueType val) {
        if (size() == capacity_) {
            expandCapacity();
        }
        values_[tail()] = val;
        count_++;
    }

    template <typename ValueType>
    ValueType Queue<ValueType>::dequeue() {
        if (isEmpty()) {
            error("dequeue: Attempting to dequeue an empty queue");
        }
        ValueType val = values_[head_];
        head_ = (head_ + 1) % capacity_;
        count_--;
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
    void Queue<ValueType>::reverse() {
        for (int i = 0; i < count_ / 2; i++) {
            int left = (head_ + i) % capacity_;
            int right = (tail() + capacity_ - 1 - i) % capacity_;
            ValueType tmp = values_[left];
            values_[left] = values_[right];
            values_[right] = tmp;
        }
    }

    template <typename ValueType>
    void Queue<ValueType>::expandCapacity() {
        ValueType* oldValues = values_;
        values_ = new ValueType[capacity_ * 2];
        for (int i = 0; i < count_; i++) {
            values_[i] = oldValues[(i + head_) % capacity_];
        }
        capacity_ *= 2;
        head_ = 0;
        delete[] oldValues;
    }

    template <typename ValueType>
    int Queue<ValueType>::tail() const {
        return (head_ + count_) % capacity_;
    }

}

#endif
