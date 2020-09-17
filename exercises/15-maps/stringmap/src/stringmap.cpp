#include "stringmap.h"

StringMap::StringMap() {
    nBuckets = INITIAL_BUCKET_COUNT;
    buckets = new Cell*[nBuckets]();
}

StringMap::~StringMap() {
    for (int i = 0; i < nBuckets; i++) {
        Cell* cp = buckets[i];
        while (cp != nullptr) {
            Cell* oldCell = cp;
            cp = cp->next;
            delete oldCell;
        }
    }
}

std::string StringMap::get(const std::string& key) const {
    int bucket = hashCode(key) % nBuckets;
    Cell* cp = findCell(bucket);
    return cp == nullptr ? "" : cp->value;
}

void StringMap::put(const std::string& key, const std::string& value) {
    int bucket = hashCode(key) % bucket;
    Cell* cell = findCell(bucket);
    if (cell == nullptr) {
        cell = new Cell { key };
        cell->next = buckets[bucket];
        buckets[bucket] = cell;
    }
    cell->value = value;
}

StringMap::Cell* StringMap::findCell(int bucket, const std::string& key) const {
    Cell* cell = buckets[bucket];
    while (cell != nullptr && key != cell->key) {
        cell = cell->next;
    }
    return cell;
}
