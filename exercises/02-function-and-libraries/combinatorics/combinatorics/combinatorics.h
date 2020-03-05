//
//  combinatorics.h
//  combinatorics
//
//  Created by Eugene Shcherbo on 9/22/19.
//  Copyright © 2019 Eugene Shcherbo. All rights reserved.
//

#ifndef combinatorics_h
#define combinatorics_h

/*
 * Function: combinations
 * Usage: int res = combinations(n, k);
 * ------------------------------------
 * Returns the number of ways to choose k elements from set of size n.
 */

int combinations(int n, int k);

/*
 * Function: permutations
 * Usage: int res = permutations(n, k);
 * ------------------------------------
 * Returns the number of ways to choose k elements in all posible order
 * from set of size n.
 */

int permutations(int n, int k);

#endif /* combinatorics_h */
