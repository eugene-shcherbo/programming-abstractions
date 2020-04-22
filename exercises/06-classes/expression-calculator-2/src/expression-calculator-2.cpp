
/*
 * File: Main.cpp
 * -----------------------
 * This program simulates an electronic calculator that uses
 * reverse Polish notation, in which operators come after
 * the operands to which they apply. Information for users
 * of this application appears in the helpCommand function.
 */

#include <iostream>
#include "simpio.h"
#include "strlib.h"
#include "console.h"
#include "tokenscanner.h"
#include "expressioncalculator.h"

using namespace std;

int main() {
    ExpressionCalculator calc;

    while (true) {
        string expr = getLine("> ");

        if (expr.empty() || expr[0] == 'Q') {
            break;
        }

        cout << calc.evaluate(expr) << endl;
    }

    return 0;
}
