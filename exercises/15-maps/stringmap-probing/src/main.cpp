#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <chrono>
#include "console.h"
#include "filelib.h"
#include "stringmap.h"

using namespace std;

string generateRandomString(size_t length) {
    string s;

    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";

    for (size_t i = 0; i < length; ++i) {
        s += alphanum[rand() % (sizeof(alphanum) - 1)];
    }

    return s;
}

string* generateRandomStrings(size_t n, size_t keylenght) {
    string* keys = new string[n]();

    for (size_t i = 0; i < n; i++) {
        keys[i] = generateRandomString(keylenght);
    }

    return keys;
}

long long measureAlgorithm(std::function<void()> algo) {
    auto t1 = std::chrono::high_resolution_clock::now();
    algo();
    auto t2 = std::chrono::high_resolution_clock::now();

    return std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
}

void testHashing(size_t n) {
    StringMap map;
    string* keys = generateRandomStrings(n, 10);
    string* values = generateRandomStrings(n, 50);

    std::function<void()> putAlgo([&] {
        for (size_t i = 0; i < n; i++) {
            map.put(keys[i], values[i]);
        }
    });

    std::function<void()> getAlgo([&] {
        for (size_t i = 0; i < n; i++) {
            map.get(keys[i]);
        }
    });

    cout << "going to put values to the map" << endl;
    long long putExecTime = measureAlgorithm(putAlgo);
    cout << "It took " << putExecTime << endl;

    cout << "going to fetch values from the map" << endl;
    long long getExecTime = measureAlgorithm(getAlgo);
    cout << "It took " << getExecTime << endl;

    delete[] keys;
    delete[] values;
}

int main() {
    testHashing(100);
    testHashing(10000);

    StringMap map;
    map.put("hello", "world");
    map.put("vlada", "zhenya");
    map.put("zhenya", "vlada");

    assert(map.get("hello") == "world");
    assert(map.get("vlada") == "zhenya");
    assert(map.get("zhenya") == "vlada");

    map.put("hello", "c++");

    assert(map.get("hello") == "c++");

    return 0;
}
