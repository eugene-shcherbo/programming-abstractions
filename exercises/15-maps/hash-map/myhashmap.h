#ifndef MyHashMap_H
#define MyHashMap_H

template <typename TKey, typename TValue>
class MyHashMap {

public:
    MyHashMap();
    ~MyHashMap();

    size_t size() const;
    bool isEmpty() const;
    void put(const TKey& key, const TValue& value);
    TValue get(const TKey& key) const;
    void remove(const TKey& key);
    bool containsKey(const TKey& key) const;
    void clear();

    TValue& operator[](const TKey& key);
    TValue operator[](const TKey& key) const;

private:
    static double constexpr LOAD_THRESHOLD = .7;
    static int constexpr INITIAL_BUCKETS_NUM = 13;

    struct Cell {
        TKey key;
        TValue value;
        Cell* next;
    };

    Cell** _buckets;
    int _bucketsNum;
    int _size;

    Cell* findCell(int bucket, const TKey& key) const;
    void expandAndRehash();

    MyHashMap& operator=(const MyHashMap& other);
    MyHashMap(const MyHashMap& other);
};

template <typename TKey, typename TValue>
MyHashMap<TKey, TValue>::MyHashMap() {
    _bucketsNum = INITIAL_BUCKETS_NUM;
    _buckets = new Cell*[_bucketsNum]();
    _size = 0;
}

template <typename TKey, typename TValue>
MyHashMap<TKey, TValue>::~MyHashMap() {
    if (!isEmpty())
        clear();
}

template <typename TKey, typename TValue>
void MyHashMap<TKey, TValue>::put(const TKey& key, const TValue& value) {
    int bucket = hashCode(key) % _bucketsNum;
    Cell* cell = findCell(bucket, key);

    if (cell == nullptr) {
        if (_size / _bucketsNum >= LOAD_THRESHOLD) {
            expandAndRehash();
            bucket = hashCode(key) % _bucketsNum;
        }
        cell = new Cell { key, value, _buckets[bucket] };
        _buckets[bucket] = cell;
        _size++;
    }

    cell->value = value;
}

template <typename TKey, typename TValue>
void MyHashMap<TKey, TValue>::expandAndRehash() {
    int oldNumBuckets = _bucketsNum;
    _bucketsNum = _bucketsNum * 2 + 1;
    Cell** oldBuckets = _buckets;
    _buckets = new Cell*[_bucketsNum]();

    for (int i = 0; i < oldNumBuckets; i++) {
        Cell* cell = _buckets[i];
        while (cell != nullptr) {
            Cell* oldCell = cell;
            put(cell->key, cell->value);
            delete oldCell;
        }
    }

    delete oldBuckets;
}

template <typename TKey, typename TValue>
TValue MyHashMap<TKey, TValue>::get(const TKey& key) const {
    int bucket = hashCode(key) % _bucketsNum;
    Cell* cell = findCell(bucket, key);
    return cell == nullptr ? TValue() : cell->value;
}

template <typename TKey, typename TValue>
void MyHashMap<TKey, TValue>::remove(const TKey& key) {
    int bucket = hashCode(key) % _bucketsNum;
    Cell* parent = nullptr;
    Cell* current = _buckets[bucket];

    while (current != nullptr && current->key != key) {
        parent = current;
        current = current->next;
    }

    if (current != nullptr) {
        if (parent == nullptr) {
            _buckets[bucket] =  current->next;
        } else {
            parent->next = current->next;
        }
        _size--;
        delete current;
    }
}

template <typename TKey, typename TValue>
struct MyHashMap<TKey, TValue>::Cell* MyHashMap<TKey, TValue>::findCell(int bucket, const TKey& key) const {
    Cell* cell = _buckets[bucket];

    while (cell != nullptr && cell->key != key) {
        cell = cell->next;
    }

    return cell;
}

template <typename TKey, typename TValue>
bool MyHashMap<TKey, TValue>::containsKey(const TKey& key) const {
    int bucket = hashCode(key) % _bucketsNum;
    Cell* cell = findCell(bucket, key);
    return cell != nullptr;
}

template <typename TKey, typename TValue>
TValue& MyHashMap<TKey, TValue>::operator[](const TKey& key) {
    put(key, TValue());
    int bucket = hashCode(key) % _bucketsNum;
    return findCell(bucket, key)->value;
}

template <typename TKey, typename TValue>
TValue MyHashMap<TKey, TValue>::operator[](const TKey& key) const {
    return get(key);
}

template <typename TKey, typename TValue>
size_t MyHashMap<TKey, TValue>::size() const {
    return _size;
}

template <typename TKey, typename TValue>
bool MyHashMap<TKey, TValue>::isEmpty() const {
    return _size == 0;
}

template <typename TKey, typename TValue>
void MyHashMap<TKey, TValue>::clear() {
    for (int i = 0; i < _bucketsNum; i++) {
        Cell* cell = _buckets[i];
        while (cell != nullptr) {
            Cell* oldCell = cell;
            cell = cell->next;
            delete oldCell;
        }
    }
    delete[] _buckets;
    _size = 0;
}


#endif // MyHashMap_H
