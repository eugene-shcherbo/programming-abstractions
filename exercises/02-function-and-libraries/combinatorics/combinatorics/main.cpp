//
//  main.cpp
//  combinatorics
//
//  Created by Eugene Shcherbo on 9/22/19.
//  Copyright © 2019 Eugene Shcherbo. All rights reserved.
//

#include <iostream>
#include "combinatorics.h"
using namespace std;

int main(int argc, const char * argv[]) {
    cout << "Combinations C(16, 2) = " << combinations(7, 6) << endl
            << "Permutations P(52, 2) = " << permutations(52, 2) << endl;
    
    return 0;
}
