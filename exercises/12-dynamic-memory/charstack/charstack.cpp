#include "charstack.h"

CharStack::CharStack() {
    capacity = INITIAL_CAPACITY;
    items = new char[capacity];
    count = 0;
}

CharStack::~CharStack() {
    delete[] items;
}

CharStack::CharStack(const CharStack& src) {
    deepCopy(src);
}

bool CharStack::isEmpty() const {
    return count == 0;
}

int CharStack::size() const {
    return count;
}

char CharStack::peek() const {
    if (isEmpty()) throw "peek: the stack is empty";

    return items[count - 1];
}

void CharStack::push(char ch) {
    if (count == capacity) {
        extendCapacity();
    }

    items[count++] = ch;
}

char CharStack::pop() {
    if (isEmpty()) throw "pop: the stack is empty";

    return items[--count];
}

void CharStack::extendCapacity() {
    char* oldItems = items;
    capacity *= 2;
    items = new char[capacity];

    for (int i = 0; i < count; i++) {
        items[i] = oldItems[i];
    }

    delete[] oldItems;
}

void CharStack::clear() {
    count = 0;
}


CharStack& CharStack::operator=(const CharStack& src) {
    if (this != &src) {
        delete[] items;
        deepCopy(src);
    }

    return *this;
}

void CharStack::deepCopy(const CharStack& src) {
    items = new char[src.capacity];

    for (int i = 0; i < src.count; i++) {
        items[i] = src.items[i];
    }

    count = src.count;
    capacity = src.capacity;
}
