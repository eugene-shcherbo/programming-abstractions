#include <iostream>
#include <string>
#include "console.h"
#include "simpio.h"
#include "tokenscanner.h"
#include "error.h"
#include "exp.h"
#include "parser.h"

using namespace std;

int main() {
    EvaluationContext context;
    TokenScanner scanner;
    Expression* exp;
    scanner.ignoreWhitespace();
    scanner.scanNumbers();

    while (true) {
        exp = nullptr;
        try {
            string line;
            cout << "=> ";
            getline(cin, line);
            if (line == "quit") break;
            scanner.setInput(line);
            exp = parseExp(scanner);
            int value = exp->eval(context);
            cout << value << endl;
        } catch (ErrorException& ex) {
            cerr << "Error: " << ex.getMessage() << endl;
        }
        if (exp != nullptr) delete exp;
    }

    return 0;
}
