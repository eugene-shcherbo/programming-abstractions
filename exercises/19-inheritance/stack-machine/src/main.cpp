#include <iostream>
#include <fstream>
#include "console.h"
#include "tokenscanner.h"
#include "map.h"
#include "exp.h"
#include "parser.h"

using namespace std;

void compile(istream& is, ostream& os);
void compileExpression(Expression* exp, ostream& os);
void compileBinary(Expression* binary, ostream& os);

static const Map<string, string> opInstructionLookup {
    { "+", "ADD" },
    { "*", "MUL" },
    { "-", "SUB" },
    { "/", "DIV" }
};

int main() {
    ifstream input("input.txt");
    compile(input, cout);

    return 0;
}

void compile(istream& is, ostream& os) {
    TokenScanner scanner;
    scanner.ignoreWhitespace();
    scanner.scanNumbers();
    string line;

    while (getline(is, line)) {
        scanner.setInput(line);
        Expression* exp = parseExp(scanner);
        compileExpression(exp, os);
        os << "DISPLAY" << endl;
        delete exp;
    }
}

void compileExpression(Expression* exp, ostream& os) {
    if (exp->getType() == CONSTANT) {
        os << "LOAD #" << exp->getConstantValue() << endl;
    } else if (exp->getType() == IDENTIFIER) {
        os << "LOAD " << exp->getIdentifierName() << endl;
    } else if (exp->getType() == BINARY) {
        compileBinary(exp, os);
    }
}

void compileBinary(Expression* binary, ostream& os) {
    string op = binary->getOperator();

    if (op == "=") {
        compileExpression(binary->getRhs(), os);
        os << "STORE " << binary->getLhs()->toString() << endl;
    } else {
        compileExpression(binary->getLhs(), os);
        compileExpression(binary->getRhs(), os);
        os << opInstructionLookup[binary->getOperator()] << endl;
    }
}
