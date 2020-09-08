#include <iostream>
#include <string>
#include "console.h"
#include "simpio.h"
#include "tokenscanner.h"
#include "error.h"
#include "set.h"
#include "exp.h"
#include "parser.h"

using namespace std;

void printInRpnNotaion(const Expression* expr);

int main() {
    TokenScanner scanner;
    scanner.ignoreWhitespace();
    scanner.scanNumbers();
    Expression* expr;
    while (true) {
        string line = getLine("> ");
        if (line == "quit") break;
        scanner.setInput(line);
        expr = parseExp(scanner);
        printInRpnNotaion(expr);
        cout << endl;
        delete expr;
    }

    return 0;
}

void printInRpnNotaion(const Expression* expr) {
    if (expr->getType() == CONSTANT) {
        cout << expr->getConstantValue() << ' ';
    } else if (expr->getType() == IDENTIFIER) {
        cout << expr->getIdentifierName() << ' ';
    } else if (expr->getType() == BINARY) {
        printInRpnNotaion(expr->getLhs());
        printInRpnNotaion(expr->getRhs());
        cout << expr->getOperator() << ' ';
    }
}
