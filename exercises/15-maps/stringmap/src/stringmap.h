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

    struct Cell {
        std::string key;
        std::string value;
        Cell* next;
    };

    static constexpr int INITIAL_BUCKET_COUNT = 13;

    Cell **buckets;
    int nBuckets;

    Cell* findCell(int bucket, const std::string& key) const;

    StringMap(const StringMap& src);
    StringMap& operator=(const StringMap& src) { return *this; }
};

#endif // STRINGMAP_H
