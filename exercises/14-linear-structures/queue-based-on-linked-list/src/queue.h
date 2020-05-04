#ifndef _queue_h_
#define _queue_h_

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
        void clear();
        void reverse();

    private:
        struct Cell {
            ValueType val;
            Cell* link;
        };

        Queue(const Queue& other);

        Cell* tail_;
        Cell* head_;
        int count_;

        Queue& operator=(const Queue& other);
    };

    template <typename ValueType>
    Queue<ValueType>::Queue() {
        tail_ = nullptr;
        head_ = nullptr;
        count_ = 0;
    }

    template <typename ValueType>
    Queue<ValueType>::~Queue() {
        clear();
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
    void Queue<ValueType>::clear() {
        while (!isEmpty()) {
            dequeue();
        }
    }

    template <typename ValueType>
    void Queue<ValueType>::enqueue(ValueType val) {
        Cell* cell = new Cell { val, nullptr };

        if (isEmpty()) {
            head_ = cell;
        } else {
            tail_->link = cell;
        }
        tail_ = cell;
        count_++;
    }

    template <typename ValueType>
    ValueType Queue<ValueType>::dequeue() {
        if (isEmpty()) {
            error("dequeue: Attempting dequeue from an empty queue");
        }
        Cell* dequeud = head_;
        ValueType result = head_->val;
        head_ = head_->link;
        if (head_ == nullptr) {
            tail_ = nullptr;
        }
        delete dequeud;
        count_--;
        return result;
    }

    template <typename ValueType>
    ValueType Queue<ValueType>::peek() const {
        if (isEmpty()) {
            error("dequeue: Attempting dequeue from an empty queue");
        }
        return head_->val;
    }

    template <typename ValueType>
    void Queue<ValueType>::reverse() {
        Cell* next;
        Cell* prev = nullptr;
        Cell* current = head_;

        while (current != nullptr) {
            next = current->link;
            current->link = prev;
            prev = current;
            current = next;
        }
        tail_ = head_;
        head_ = prev;
    }

}


#endif
