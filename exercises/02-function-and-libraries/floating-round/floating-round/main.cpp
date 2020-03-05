//
//  main.cpp
//  floating-round
//
//  Created by Eugene Shcherbo on 9/22/19.
//  Copyright © 2019 Eugene Shcherbo. All rights reserved.
//

#include <iostream>
using namespace std;

/* Function prototypes */

int round(double n);
void testRound();
void assertEqual(int lv, int rv);

int main(int argc, const char * argv[]) {
    testRound();
    return 0;
}

void testRound() {
    assertEqual(5, round(5.4));
    assertEqual(5, round(5.2));
    assertEqual(6, round(5.9));
    assertEqual(6, round(5.5));
    assertEqual(-5, round(-5.4));
    assertEqual(-6, round(-5.8));
}

void assertEqual(int lv, int rv) {
    if (lv == rv) {
        cout << "SUCCESS: " << lv << " == " << rv << endl;
    } else {
        cout << "FAILED: " << lv << " != " << rv << endl;
    }
}

int round(double n) {
    if (n >= 0) {
        return int(n + 0.5);
    } else {
        return int(n - 0.5);
    }
}
