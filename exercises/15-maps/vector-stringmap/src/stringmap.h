#ifndef STRINGMAP_H
#define STRINGMAP_H

#include <string>
#include "vector.h"

class StringMap {
public:
    StringMap(uint capacity = 10);
    ~StringMap();

    std::string get(const std::string& key) const;
    void put(const std::string& key, const std::string& value);

private:

    struct KeyValuePair {
        std::string key;
        std::string value;
    };

    int _size;
    int _capacity;

   KeyValuePair* bindings;

    int findKey(const std::string& key) const;
    int findKeyBinarySearch(const std::string& key, int from, int to) const;
    void insert(int index, KeyValuePair pair);
    void expandCapacity();
};

#endif // STRINGMAP_H
