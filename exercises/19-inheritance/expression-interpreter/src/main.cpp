#include <iostream>
#include <string>
#include "console.h"
#include "simpio.h"
#include "tokenscanner.h"
#include "error.h"
#include "strlib.h"
#include "set.h"
#include "exp.h"
#include "parser.h"
#include "exputil.h"

using namespace std;

void testMainFlow();
void testChangeVariable();
void testExpMatch();
void testExpMatch(string expInput1, string expInput2);
void testFoldConstants();
void testFoldConstants(string origexp);
void testUnparse(string expr);
void testUnparse();
void testDifferentiate();
void testDifferentiate(string expr);

/* Expression Utility Functions */

Expression* createFromString(string exp);

int main() {
    testMainFlow();
    testChangeVariable();
    testExpMatch();
    testFoldConstants();
    testUnparse();
    testDifferentiate();

    return 0;
}

void listVariables(Expression* exp) {
    Set<std::string> variables;
    yieldVariables(exp, variables);

    for (std::string variable : variables) {
        std::cout << variable << std::endl;
    }
}

void testMainFlow() {
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
            double value = exp->eval(context);
            cout << value << endl;
            cout << "Used variables: " << endl;
            listVariables(exp);
        } catch (ErrorException& ex) {
            cerr << "Error: " << ex.getMessage() << endl;
        }
        if (exp != nullptr) delete exp;
    }
}

void testChangeVariable() {
    cout << "---Change variable test---" << endl;

    string testExp = "z = 3 * x * x - 4 * x - 2 * a + y";
    Expression* exp = createFromString(testExp);

    cout << "Given: " << exp->toString() << endl << endl;
    cout << "change: 'x' to 't'" << endl << endl;

    Expression* newExpr = changeVariable(exp, "x", "t");

    cout << "new: " << newExpr->toString() << endl;
    cout << "old: " << exp->toString() << endl << endl;

    delete newExpr;
    delete exp;
}

void testExpMatch() {
    cout << "---Expression match test----" << endl;

    testExpMatch("x", "x");
    testExpMatch("x", "y");
    testExpMatch("x = y + z + 5 + t + v", "x = y + z + 5 + v + t");
    testExpMatch("x = y + z + 5 + t + v", "x = y + z + 5 + t + v");
    testExpMatch("x = y + z + 5 + t + v", "x = y + z + 3 + t + v");
}

void testExpMatch(string expInput1, string expInput2) {
    Expression* exp1 = createFromString(expInput1);
    Expression* exp2 = createFromString(expInput2);

    cout << "exp1: " << exp1->toString() << endl;
    cout << "exp2: " << exp2->toString() << endl;

    cout << "Result: " << (expMatch(exp1, exp2) ? "match" : "not match") << endl;

    delete exp1;
    delete exp2;
}

void testFoldConstants() {
    cout << "--- Fold Constants test ---" << endl;
    testFoldConstants("1 + 2 + 3");
    testFoldConstants("24 * 60 * 60 * sec");
    testFoldConstants("24 + 3 * x");
    testFoldConstants("24 * -60 * 60 * sec");
}

void testFoldConstants(string origexp) {
    Expression* e1 = createFromString(origexp);
    Expression* e2 = foldConstants(e1);

    cout << "Was: " << e1->toString() << endl;
    cout << "Now: " << e2->toString() << endl;

    delete e1;
    delete e2;
}

void testUnparse() {
    cout << "--- Unparse test ---" << endl;
    testUnparse("y = 3 * (x + 1)");
    testUnparse("y = 3 + (x + 1)");
    testUnparse("y = 3 * (x * (y + 1))");
    testUnparse("y = 3 * (x * y + 1)");
}

void testUnparse(string expr) {
    Expression* e = createFromString(expr);

    cout << "original: " << expr << endl;
    cout << "toString: " << e->toString() << endl;
    cout << "unparsed: " << unparse(e) << endl;

    delete e;
}

void testDifferentiate() {
    cout << endl << "--- Differentiate test ---" << endl;

    testDifferentiate("2 * x + 3 * y");
    testDifferentiate("3 * x * x");
    // testDifferentiate("3 * x * x + 3 * y / x - c");
    /*testDifferentiate("y");
    testDifferentiate("2 * x + 3 * y");*/
}

void testDifferentiate(string expr) {
    Expression* e = createFromString(expr);
    cout << '(' << unparse(e) << ")' = " << unparse(differentiate(e, "x")) << endl;
    delete e;
}

Expression* createFromString(string exp) {
    TokenScanner scanner;
    scanner.ignoreWhitespace();
    scanner.scanNumbers();
    scanner.setInput(exp);
    return parseExp(scanner);
}
