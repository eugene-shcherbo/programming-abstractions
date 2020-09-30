#include "stringmap.h"
#include "hashcode.h"
#include "error.h"

StringMap::StringMap() {
    _capacity = INITIAL_BUCKET_COUNT;
    _pairs = new KeyValuePair*[_capacity]();
    _entries = 0;
}

StringMap::~StringMap() {
    delete[] _pairs;
}

std::string StringMap::get(const std::string& key) const {
    int entryIndex = findEntry(key);
    return _pairs[entryIndex] == nullptr ? "" : _pairs[entryIndex]->value;
}

void StringMap::put(const std::string& key, const std::string& value) {
    int entryIndex = findEntry(key);

    if (_pairs[entryIndex] == nullptr) {
        _pairs[entryIndex] = new KeyValuePair { key, value };
        _entries++;
    } else {
        _pairs[entryIndex]->value = value;
    }

    if (loadFactor() >= REHASH_THRESHOLD)
        extendAndRehash();
}

int StringMap::findEntry(const std::string& key) const {
    int index = hashCode(key) % _capacity;
    int emptyIndex = -1;
    int count = 0;

    while (count < _capacity) {
        if (_pairs[index] == nullptr) {
            emptyIndex = index;
        } else if (_pairs[index]->key == key) {
            return index;
        }
        index = (index + 1) % _capacity;
        count++;
    }

    return emptyIndex;
}

void StringMap::extendAndRehash() {
    KeyValuePair** oldEntries = _pairs;
    int oldCapacity = _capacity;
    _capacity = _capacity * 2 + 1;
    _pairs = new KeyValuePair*[_capacity]();
    _entries = 0;

    for (int i = 0; i < oldCapacity; i++) {
        KeyValuePair* oldPair = _pairs[i];

        if (oldPair != nullptr) {
            put(oldPair->key, oldPair->value);
            delete oldPair;
        }
    }

    delete[] oldEntries;
}
