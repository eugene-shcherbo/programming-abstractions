#include <iostream>
#include <sstream>
#include "console.h"
#include "vector.h"
#include "myhashmap.h"

using namespace std;

bool twoSum(Vector<int>& nums, int target, int& index1, int& index2);
void testTwoSum(Vector<int> nums, int target);
void testMapMethods();

struct Employee {
    std::string name;
    std::string jobTitle;

    std::string toString() const {
        std::ostringstream ss;
        ss << "name: " << name << std::endl;
        ss << "job title: " << jobTitle << std::endl;
        return ss.str();
    }
};

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
    MyHashMap<string, string> map;
    string* keys = generateRandomStrings(n, 10);
    string* values = generateRandomStrings(n, 50);

    std::function<void()> putAlgo([&] {
        for (size_t i = 0; i < n; i++) {
            map[keys[i]] = values[i];
        }
    });

    std::function<void()> getAlgo([&] {
        for (size_t i = 0; i < n; i++) {
            map[keys[i]];
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
    testTwoSum(Vector<int> { 2, 7, 11, 15 }, 9);
    testTwoSum(Vector<int> { 3, 2, 4 }, 6);
    testTwoSum(Vector<int> { 3, 3 }, 6);

    testHashing(1000);
    testHashing(10000);
    testHashing(100000);
    testHashing(1000000);

    std::cout << std::endl << "All tests are passed..." << std::endl;

    return 0;
}

void testMapMethods() {
    MyHashMap<std::string, Employee*> employees;

    assert(employees.isEmpty());
    assert(employees.size() == 0);

    employees.put("Jon Skeet", new Employee { "Jon Skeet", "Lead Software Engineer" });
    employees.put("Eric Lippert", new Employee { "Eric Lippert", "Lead Software Engineer" });
    employees.put("Jon Skeet", new Employee { "Eric Lippert", "Lead Software Engineer at Google" });

    assert(!employees.isEmpty());
    assert(employees.size() == 2);
    assert(employees.containsKey("Jon Skeet"));
    assert(employees.containsKey("Eric Lippert"));

    std::cout << employees.get("Jon Skeet")->toString() << std::endl;
    std::cout << employees.get("Eric Lippert")->toString() << std::endl;

    employees.remove("Jon Skeet");
    assert(employees.size() == 1);

    employees.remove("Eric Lippert");
    assert(employees.size() == 0);
    assert(employees.isEmpty());

    employees.put("Jon Skeet", nullptr);
    assert(!employees.isEmpty());

    MyHashMap<int, std::string> integers;
    integers.put(13, "hello world");
    integers.put(26, "good buy");
    assert(integers.size() == 2);
    integers.remove(13);
    integers.remove(26);
    assert(integers.isEmpty());

    integers.clear();
    employees.clear();

    assert(integers.isEmpty());
    assert(employees.isEmpty());
}

void testTwoSum(Vector<int> nums, int target) {
    int index1, index2;

    if (twoSum(nums, target, index1, index2)) {
        std::cout << "index1 = " << index1 << ", index2 = " << index2 << std::endl;
    } else {
        std::cout << "No sum." << std::endl;
    }
}

bool twoSum(Vector<int>& nums, int target, int& index1, int& index2) {
    MyHashMap<int, int> indexes;

    for (int i = 0; i < nums.size(); i++) {
        int remain = target - nums[i];

        if (indexes.containsKey(remain)) {
            index1 = indexes[remain];
            index2 = i;
            return true;
        }

        indexes[nums[i]] =  i;
    }

    return false;
}
