#include <iostream>
#include "set.h"
#include "console.h"

using namespace std;

bool subsetSumExists(const Set<int>& set, int target);

int main() {

    cout << subsetSumExists(Set<int> { -2, 1, 3, 8 }, 7) << endl << endl;
    cout << subsetSumExists(Set<int> { -2, 1, 3, 8 }, 5) << endl << endl;

    return 0;
}

bool subsetSumExists(const Set<int>& set, int target) {
    if (set.isEmpty()) {
        return target == 0;
    } else {
        int el = set.first();
        Set<int> rest = set - el;
        return subsetSumExists(rest, target)
                || subsetSumExists(rest, target - el);
    }
}
