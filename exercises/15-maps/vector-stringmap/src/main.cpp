#include <iostream>
#include <fstream>
#include <string>
#include "console.h"
#include "stringmap.h"

using namespace std;

void testMap();

int main() {
    testMap();
    return 0;
}

void testMap() {
    StringMap map(2);
    assert(map.isEmpty());

    map.put("BK", "ALASKA");
    map.put("ID", "IDAHO");
    map.put("MT", "MONTANA");
    map.put("AK", "LOL");

    assert(map.get("BK") == "ALASKA");
    assert(map.get("ID") == "IDAHO");
    assert(map.get("MT") == "MONTANA");
    assert(map.get("AK") == "LOL");

    assert(map.size() == 4);
    assert(!map.isEmpty());

    assert(map.containsKey("BK"));
    assert(!map.containsKey("ML"));

    map.clear();
    assert(map.isEmpty());
    assert(!map.containsKey("BK"));
}
