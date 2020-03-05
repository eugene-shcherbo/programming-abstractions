#include <iostream>
#include "hist.h"
#include "console.h"
using namespace std;

int main() {
    Vector<int> data { 11, 12, 13, 15, 21, 25, 45, 65, 11, 28, 19, 100, 150, 87 };

    printHistogram(data, 0, 200, 5, '&');

    return 0;
}
