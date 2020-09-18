#include "stringmap.h"
#include "hashcode.h"

StringMap::StringMap() {
    nBuckets = INITIAL_BUCKET_COUNT;
    buckets = new Cell*[nBuckets]();
    nEntries = 0;
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
    Cell* cp = findCell(bucket, key);
    return cp == nullptr ? "" : cp->value;
}

void StringMap::put(const std::string& key, const std::string& value) {
    int bucket = hashCode(key) % nBuckets;
    Cell* cell = findCell(bucket, key);

    if (cell == nullptr) {

        if (isLoaded()) {
            extendBuckets();
            bucket = hashCode(key) % nBuckets;
        }

        cell = new Cell();
        cell->key = key;
        cell->next = buckets[bucket];
        buckets[bucket] = cell;
        nEntries++;
    }

    cell->value = value;
}

StringMap::Cell* StringMap::findCell(int bucket, const std::string& key) const {
    Cell* cell = buckets[bucket];
    while (cell != nullptr && cell->key != key) {
        if (key == cell->key) break;
        cell = cell->next;
    }
    return cell;
}

void StringMap::extendBuckets() {
    Cell** oldBuckets = buckets;
    int oldBucketNum = nBuckets;
    nBuckets = nBuckets * 2 + 1;
    buckets = new Cell*[nBuckets]();

    for (int i = 0; i < oldBucketNum; i++) {
        Cell* cell = oldBuckets[i];

        // rehash
        while (cell != nullptr) {
            Cell* oldCell = cell;
            put(cell->key, cell->value);
            cell = cell->next;
            delete oldCell;
        }
    }

    delete oldBuckets;
}

bool StringMap::isLoaded() const {
    return (nEntries / nBuckets) >= REHASH_THRESHOLD;
}
