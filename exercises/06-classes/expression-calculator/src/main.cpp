
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

using namespace std;

double calculate(TokenScanner& tokens);
double calculate(double lOperand, double rOperand, char op);

int main() {
    TokenScanner scanner;
    scanner.ignoreWhitespace();
    scanner.scanNumbers();

    while (true) {
        string expr = getLine("> ");

        if (expr.empty() || expr[0] == 'Q') {
            break;
        }

        scanner.setInput(expr);
        cout << calculate(scanner) << endl;
    }

    return 0;
}

double calculate(TokenScanner& tokens) {
    double leftOperand = stringToReal(tokens.nextToken());

    while (tokens.hasMoreTokens()) {
        string op =  tokens.nextToken();
        double rightOperand = stringToReal(tokens.nextToken());
        leftOperand = calculate(leftOperand, rightOperand, op[0]);
    }

    return leftOperand;
}

double calculate(double lOperand, double rOperand, char op) {
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
