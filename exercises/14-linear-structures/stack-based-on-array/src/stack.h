
#ifndef _stack_h_
#define _stack_h_

#include "error.h"

namespace collections {

    template <typename ValueType>
    class Stack {
    public:
        Stack();
        Stack(const Stack& other);
        ~Stack();

        bool isEmpty() const;
        int size() const;
        void clear();
        ValueType peek() const;
        void push(ValueType val);
        ValueType pop();

        Stack& operator= (const Stack& other);

    private:
        static constexpr int INITIAL_CAPACITY = 10;

        int size_;
        int capacity_;
        ValueType* values_;

        void expandCapacity();
        void deepCopy(const Stack& other);
    };

    template <typename ValueType>
    Stack<ValueType>::Stack() {
        capacity_ = INITIAL_CAPACITY;
        size_ = 0;
        values_ = new ValueType[capacity_];
    }

    template <typename ValueType>
    Stack<ValueType>::Stack(const Stack& other) {
        deepCopy(other);
    }

    template <typename ValueType>
    Stack<ValueType>::~Stack<ValueType>() {
        delete[] values_;
    }

    template <typename ValueType>
    bool Stack<ValueType>::isEmpty() const {
        return size_ == 0;
    }

    template <typename ValueType>
    int Stack<ValueType>::size() const {
        return size_;
    }

    template <typename ValueType>
    void Stack<ValueType>::clear() {
        size_ = 0;
    }

    template <typename ValueType>
    ValueType Stack<ValueType>::peek() const {
        if (isEmpty()) {
            error("error: stack is empty");
        }
        return values_[size_ - 1];
    }

    template <typename ValueType>
    void Stack<ValueType>::push(ValueType val) {
        if (size_ == capacity_) {
            expandCapacity();
        }
        values_[size_++] = val;
    }

    template <typename ValueType>
    ValueType Stack<ValueType>::pop() {
        ValueType val = peek();
        size_--;
        return val;
    }

    template <typename ValueType>
    Stack<ValueType>& Stack<ValueType>::operator=(const Stack& other) {
        if (this != &other) {
            delete[] values_;
            deepCopy(other);
        }
        return *this;
    }

    template <typename ValueType>
    void Stack<ValueType>::expandCapacity() {
        ValueType* oldValues = values_;
        capacity_ *= 2;
        values_ = new ValueType[capacity_];
        for (int i = 0; i < size_; i++) {
            values_[i] = oldValues[i];
        }
        delete[] oldValues;
    }

    template <typename ValueType>
    void Stack<ValueType>::deepCopy(const Stack& other) {
        capacity_ = other.capacity_;
        size_ = other.size_;
        values_ = new ValueType[capacity_];
        for (int i = 0; i < size_; i++) {
            values_[i] = other.values_[i];
        }
    }

}

#endif
