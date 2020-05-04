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

        ValueType* values_;
        int size_;
        int capacity_;

        void expandCapacity();
        void deepCopy(const Vector& other);
    };

    template <typename ValueType>
    Vector<ValueType>::Vector() {
        capacity_ = INITIIAL_CAPACITY;
        size_ = 0;
        values_ = new ValueType[capacity_];
    }

    template <typename ValueType>
    Vector<ValueType>::Vector(int n, const ValueType& val) {
        capacity_ = n > INITIIAL_CAPACITY ? n : INITIIAL_CAPACITY;
        size_ = n;
        values_ = new ValueType[capacity_];
        for (int i = 0; i < size_; i++) {
            values_[i] = val;
        }
    }

    template <typename ValueType>
    Vector<ValueType>::Vector(const Vector& other) {
        deepCopy(other);
    }

    template <typename ValueType>
    Vector<ValueType>::~Vector() {
        delete[] values_;
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
    void Vector<ValueType>::clear() {
        size_ = 0;
    }

    template <typename ValueType>
    const ValueType& Vector<ValueType>::get(int index) const {
        if (index < 0 || index >= size_) {
            error("get: attempting the get item with index which is outside the vectors");
        }
        return values_[index];
    }

    template <typename ValueType>
    void Vector<ValueType>::set(int index, const ValueType& val) {
        if (index < 0 || index >= size_) {
            error("set: attempting to set item with index which is outside the vectors");
        }
        values_[index] = val;
    }

    template <typename ValueType>
    void Vector<ValueType>::insert(int index, const ValueType& val) {
        if (index < 0 || index > size_) {
            error("Attempting to insert item to the index which is outside the vectors");
        } else if (size_ == capacity_) {
            expandCapacity();
        }

        for (int i = size_; i > index; i--) {
            values_[i] = values_[i - 1];
        }
        values_[index] = val;
        size_++;

    }

    template <typename ValueType>
    void Vector<ValueType>::add(const ValueType& val) {
        insert(size_, val);
    }

    template <typename ValueType>
    void Vector<ValueType>::remove(int index) {
        if (index < 0 || index >= size_) {
            error("remove: attempting to remove item with index which is outside the vectors");
        }

        for (int i = index; i < size_ - 1; i++) {
            values_[i] = values_[i + 1];
        }
        size_--;
    }

    template <typename ValueType>
    const ValueType& Vector<ValueType>::operator[](int index) const {
        return get(index);
    }

    template <typename ValueType>
    ValueType& Vector<ValueType>::operator[](int index) {
        if (index < 0 || index >= size_) {
            error("attempting to get item with index which is outside the vectors");
        }
        return values_[index];
    }

    template <typename ValueType>
    Vector<ValueType>& Vector<ValueType>::operator=(const Vector& other) {
        if (this != &other) {
            delete[] values_;
            deepCopy(other);
        }
        return *this;
    }

    template <typename ValueType>
    void Vector<ValueType>::expandCapacity() {
        capacity_ *= 2;
        ValueType* oldValues = values_;
        values_ = new ValueType[capacity_];
        for (int i = 0; i < size_; i++) {
            values_[i] = oldValues[i];
        }
        delete[] oldValues;
    }

    template <typename ValueType>
    void Vector<ValueType>::deepCopy(const Vector& other) {
        capacity_ = other.capacity_;
        size_ = other.size_;
        values_ = new ValueType[capacity_];
        for (int i = 0; i < size_; i++) {
            values_[i] = other.values_[i];
        }
    }

}


#endif
