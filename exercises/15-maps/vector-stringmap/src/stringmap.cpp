#include "stringmap.h"

StringMap::StringMap(uint capacity) {
    _size = 0;
    _capacity = capacity;
    bindings = new KeyValuePair[_capacity];
}

StringMap::~StringMap() {
    delete[] bindings;
}

std::string StringMap::get(const std::string& key) const {
    int index = findKey(key);
    return index == -1 ? "" : bindings[index].value;
}

void StringMap::put(const std::string& key, const std::string& value) {
    if (_size == _capacity) {
        expandCapacity();
    }

    int index = findKey(key);

    KeyValuePair entry;
    entry.key = key;

    if (index == _size) {
        index = _size;
        bindings[_size++] = entry;
    } else if (bindings[index].key != key) {
        insert(index, entry);
        _size++;
    }

    bindings[index].value = value;
}

int StringMap::findKey(const std::string& key) const {
    return findKeyBinarySearch(key, 0, _size - 1);
}

int StringMap::findKeyBinarySearch(const std::string &key, int from, int to) const {
    int center = (from + to) / 2;

    if (from > to) return from;
    else if (bindings[center].key == key) return center;
    else if (bindings[center].key < key) return findKeyBinarySearch(key, center + 1, to);

    return findKeyBinarySearch(key, from, center - 1);
}

void StringMap::insert(int index, KeyValuePair pair) {
    for (int i = _size; i > index; i--) {
        bindings[i] = bindings[i - 1];
    }
    bindings[index] = pair;
}

void StringMap::expandCapacity() {
    _capacity *= 2;
    KeyValuePair* oldBindings = bindings;
    bindings = new KeyValuePair[_capacity];

    for (int i = 0; i < _size; i++) {
        bindings[i] = oldBindings[i];
    }

    delete[] oldBindings;
}
