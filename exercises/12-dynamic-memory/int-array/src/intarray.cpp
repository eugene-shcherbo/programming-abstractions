#include "error.h"
#include "intarray.h"

IntArray::IntArray(unsigned long n) {
    capacity_ = n;
    array_ = new int[capacity_]();
}

IntArray::IntArray(const IntArray& other) {
    deepCopy(other);
}

IntArray::~IntArray() {
    delete[] array_;
}

unsigned long IntArray::size() {
    return capacity_;
}

int IntArray::get(unsigned long k) {
    if (!inBounds(k)) {
        error("get: the index passes is outside the array bounds");
    }
    return array_[k];
}

void IntArray::put(unsigned long k, int val) {
    if (!inBounds(k)) {
        error("put: the index passed is outside the array bounds");
    }
    array_[k] = val;
}

int& IntArray::operator[](unsigned long k) {
    if (!inBounds(k)) {
        error("the index passed is outside the array bounds");
    }
    return array_[k];
}

IntArray& IntArray::operator=(const IntArray& other) {
    if (this != &other) {
        delete[] array_;
        deepCopy(other);
    }
    return *this;
}

bool IntArray::inBounds(unsigned long pos) {
    return pos < capacity_;
}

void IntArray::deepCopy(const IntArray& other) {
    capacity_ = other.capacity_;
    array_ = new int[capacity_];
    for (unsigned long i = 0; i < capacity_; i++) {
        array_[i] = other.array_[i];
    }
}
