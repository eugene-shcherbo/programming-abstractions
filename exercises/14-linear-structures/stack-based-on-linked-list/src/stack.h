#ifndef _stack_h_
#define _stack_h_

namespace collections {
    template <typename ValueType>
    class Stack {
    public:
        Stack();
        Stack(const Stack& other);
        ~Stack();

        bool isEmpty() const;
        int size() const;
        void push(ValueType type);
        ValueType pop();
        ValueType peek() const;
        void clear();

        Stack& operator=(const Stack& other);
    private:
        struct Cell {
            ValueType val;
            Cell* link;
        };

        Cell* listHandle_;
        int count_;

        void deepCopy(const Stack& other);
        void copy(const Cell* cell);
    };

    template <typename ValueType>
    Stack<ValueType>::Stack() {
        listHandle_ = nullptr;
        count_ = 0;
    }

    template <typename ValueType>
    Stack<ValueType>::Stack(const Stack& other) {
        deepCopy(other);
    }

    template <typename ValueType>
    Stack<ValueType>::~Stack() {
        clear();
    }

    template <typename ValueType>
    bool Stack<ValueType>::isEmpty() const {
        return count_ == 0;
    }

    template <typename ValueType>
    int Stack<ValueType>::size() const {
        return count_;
    }

    template <typename ValueType>
    void Stack<ValueType>::push(ValueType val) {
        Cell* newCell = new Cell { val, listHandle_ };
        listHandle_ = newCell;
        count_++;
    }

    template <typename ValueType>
    ValueType Stack<ValueType>::pop() {
        if (isEmpty()) {
            error("pop: the stack is empty");
        }
        Cell* oldCell = listHandle_;
        ValueType val = oldCell->val;
        listHandle_ = listHandle_->link;
        delete oldCell;
        count_--;
        return val;
    }

    template <typename ValueType>
    ValueType Stack<ValueType>::peek() const {
        if (isEmpty()) {
            error("peek: the stack is empty");
        }
        return listHandle_->val;
    }

    template <typename ValueType>
    void Stack<ValueType>::clear() {
        while (!isEmpty()) {
            pop();
        }
    }

    template <typename ValueType>
    Stack<ValueType>& Stack<ValueType>::operator=(const Stack& other) {
        if (this != &other) {
            clear();
            deepCopy(other);
        }
        return *this;
    }

    template <typename ValueType>
    void Stack<ValueType>::deepCopy(const Stack& other) {
        count_ = 0;
        copy(other.listHandle_);
    }

    template <typename ValueType>
    void Stack<ValueType>::copy(const Cell* cell) {
        if (cell != nullptr) {
            copy(cell->link);
            push(cell->val);
        }
    }
}

#endif
