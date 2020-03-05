//
//  combinatorics.cpp
//  combinatorics
//
//  Created by Eugene Shcherbo on 9/22/19.
//  Copyright © 2019 Eugene Shcherbo. All rights reserved.
//

#include "combinatorics.h"

int combinations(int n, int k) {
    int res = 1;
    for (int i = 0; i < k; ++i)
    {
        res *= (n - i);
        res /= (i + 1);
    }
    return res;
}

int permutations(int n, int k) {
    int result = 1;
    for (int i = n - k + 1; i <= n; ++i) {
        result *= i;
    }
    return result;
}
