
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
#include "numeric.h"
#include "console.h"
#include "tokenscanner.h"

using namespace std;

string eval(TokenScanner& tokens);
int calculate(int lOperand, int rOperand, char op);

int main() {
    TokenScanner scanner;
    scanner.ignoreWhitespace();

    while (true) {
        string expr = getLine("> ");

        if (expr.empty() || expr[0] == 'Q') {
            break;
        }

        scanner.setInput(expr);
        cout << eval(scanner) << endl;
    }

    return 0;
}

string eval(TokenScanner& tokens) {
    int leftOperand = numeric::stringToInteger(tokens.nextToken(), 16);

    while (tokens.hasMoreTokens()) {
        string op =  tokens.nextToken();
        int rightOperand = numeric::stringToInteger(tokens.nextToken(), 16);
        leftOperand = calculate(leftOperand, rightOperand, op[0]);
    }

    return numeric::integerToString(leftOperand, 16);
}

int calculate(int lOperand, int rOperand, char op) {
    switch (op) {
        case '+':
            return lOperand + rOperand;
        case '-':
            return lOperand - rOperand;
        case '/':
            return lOperand / rOperand;
        case '*':
            return lOperand * rOperand;
    }

    return lOperand;
}
