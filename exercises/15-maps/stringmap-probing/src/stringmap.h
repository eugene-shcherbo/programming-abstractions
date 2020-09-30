#ifndef STRINGMAP_H
#define STRINGMAP_H

#include <string>

class StringMap {
public:
    StringMap();
    ~StringMap();

    std::string get(const std::string& key) const;
    void put(const std::string& key, const std::string& value);

private:

    struct KeyValuePair {
        std::string key;
        std::string value;
    };

    static constexpr int INITIAL_BUCKET_COUNT = 13;

    KeyValuePair** _pairs;
    int _capacity;
    int _entries;

    StringMap(const StringMap& src);
    StringMap& operator=(const StringMap& src) { return *this; }

    void putInFirstFreeCell(int startFrom, const std::string& key, const std::string& value);
    int findEntry(const std::string& key) const;
};

#endif // STRINGMAP_H
