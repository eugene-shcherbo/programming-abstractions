#include <iostream>
#include "console.h"
#include "vector.h"

using namespace std;

bool isMeasurable(int target, const Vector<int>& weights);
string yesOrNo(bool val) { return val ? "yes" : "no"; }

int main() {
    Vector<int> weights1 { 1, 3 };
    Vector<int> weights2 { 3, 5 };
    Vector<int> weights3 { 1, 2 };

    cout << yesOrNo(isMeasurable(2, weights1)) << endl;
    cout << yesOrNo(isMeasurable(5, weights1)) << endl;
    cout << yesOrNo(isMeasurable(2, weights2)) << endl;
    cout << yesOrNo(isMeasurable(2, weights3)) << endl;

    return 0;
}

bool isMeasurable(int target, const Vector<int>& weights) {
    if (weights.isEmpty()) {
        return target == 0;
    } else {
        Vector<int> rest = weights;
        int last = rest.removeBack();

        return isMeasurable(target, rest)
                || isMeasurable(target - last, rest)
                || isMeasurable(target + last, rest);
    }
}
