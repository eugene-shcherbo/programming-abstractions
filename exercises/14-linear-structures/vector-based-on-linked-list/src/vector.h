#ifndef _vector_h_
#define _vector_h_

#include "error.h"

namespace collections {

    template <typename ValueType>
    class Vector {

    public:
        Vector();
        Vector(int n, const ValueType& val = ValueType());
        Vector(const Vector& other);
        ~Vector();

        bool isEmpty() const;
        int size() const;
        void clear();
        void add(const ValueType& val);
        void insert(int index, const ValueType& val);
        void remove(int index);
        const ValueType& get(int index) const;
        void set(int index, const ValueType& val);

        const ValueType& operator[](int index) const;
        ValueType& operator[](int index);
        Vector& operator=(const Vector& other);

    private:
        static constexpr int INITIIAL_CAPACITY = 10;

        struct Cell {
            ValueType val;
            Cell* next;
        };

        Cell* list_;
        int size_;
        int capacity_;

        void deepCopy(const Vector& other);
    };

    template <typename ValueType>
    Vector<ValueType>::Vector() {
        size_ = 0;
        list_ = nullptr;
    }

    template <typename ValueType>
    Vector<ValueType>::Vector(int n, const ValueType& val) {
        size_ = n;
        Cell* curr = nullptr;
        for (int i = 0; i < size_; i++) {
            Cell* newNode = new Cell { val, nullptr };
            if (curr == nullptr) {
                list_ = newNode;
            } else {
                curr->next = newNode;
            }
            curr = newNode;
        }
    }

    template <typename ValueType>
    Vector<ValueType>::Vector(const Vector& other) {
        list_ = nullptr;
        deepCopy(other);
    }

    template <typename ValueType>
    Vector<ValueType>::~Vector() {
        clear();
    }

    template <typename ValueType>
    int Vector<ValueType>::size() const {
        return size_;
    }

    template <typename ValueType>
    bool Vector<ValueType>::isEmpty() const {
        return size() == 0;
    }

    template <typename ValueType>
    const ValueType& Vector<ValueType>::get(int index) const {
        if (index < 0 || index >= size()) {
            throw "the index is outside the vector";
        } else {
            Cell* curr = list_;
            for (int i = 0; i < index; i++) {
                curr = curr->next;
            }
            return curr->val;
        }
    }

    template <typename ValueType>
    void Vector<ValueType>::set(int index, const ValueType& val) {
        if (index < 0 || index >= size()) {
            error("the index is outside the vector");
        } else {
            Cell* curr = list_;
            for (int i = 0; i < index; i++) {
                curr = curr->next;
            }
            curr->val = val;
        }
    }

    template <typename ValueType>
    void Vector<ValueType>::add(const ValueType& val) {
        insert(size_, val);
    }

    template <typename ValueType>
    void Vector<ValueType>::insert(int index, const ValueType& val) {
        if (index < 0 || index > size()) {
            error("error: index is out of range");
        } else if (index == 0) {
            Cell* newNode = new Cell { val, list_ };
            list_ = newNode;
        } else {
            Cell* cell = new Cell { val, nullptr };
            Cell* curr = list_;
            for (int i = 0; i < index - 1; i++) {
                curr = curr->next;
            }
            cell->next = curr->next;
            curr->next = cell;
        }
        size_++;
    }

    template <typename ValueType>
    void Vector<ValueType>::remove(int index) {
        if (index < 0 || index >= size()) {
            error("error: index is out of range");
        } else if (index == 0) {
            Cell* old = list_;
            list_ = list_->next;
            delete old;
        } else {
            Cell* curr = list_;
            for (int i = 0; i < index - 1; i++) {
                curr = curr->next;
            }
            Cell* old = curr->next;
            curr->next = old->next;
            delete old;
        }
        size_--;
    }

    template <typename ValueType>
    void Vector<ValueType>::clear() {
        Cell* curr = list_;
        while (curr != nullptr) {
            list_ = list_->next;
            delete curr;
            curr = list_;
        }
    }

    template <typename ValueType>
    const ValueType& Vector<ValueType>::operator[] (int index) const {
        return get(index);
    }

    template <typename ValueType>
    ValueType& Vector<ValueType>::operator[] (int index) {
        if (index < 0 || index >= size()) {
            throw "the index is outside the vector";
        } else {
            Cell* curr = list_;
            for (int i = 0; i < index; i++) {
                curr = curr->next;
            }
            return curr->val;
        }
    }

    template <typename ValueType>
    Vector<ValueType>& Vector<ValueType>::operator= (const Vector& other) {
        if (this != &other) {
            clear();
            deepCopy(other);
        }
        return *this;
    }

    template <typename ValueType>
    void Vector<ValueType>::deepCopy(const Vector& other) {
        size_ = other.size_;
        Cell* tail = nullptr;
        for (Cell* curr = other.list_; curr != nullptr; curr = curr->next) {
            Cell* newNode = new Cell { curr->val };
            if (tail == nullptr) {
                list_ = newNode;
            } else {
                tail->next = newNode;
            }
            tail = newNode;
        }
        if (tail != nullptr) {
            tail->next = nullptr;
        }
    }
}


#endif
