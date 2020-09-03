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

bool expMatch(Expression* exp1, Expression* exp2);
Expression* createFromString(string exp);
void testExpMatch(string expInput1, string expInput2);
void testExpMatch();

void yieldVariables(Expression* exp, Set<string>& variables);
void listVariables(Expression* exp);

Expression* changeVariable(Expression* exp, std::string oldName, std::string newName);
void testChangeVariable();

int main() {
    /*EvaluationContext context;
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

    testChangeVariable();*/
    testExpMatch();

    return 0;
}

Expression* changeVariable(Expression* exp, std::string oldName, std::string newName) {
    ExpressionType expType = exp->getType();

    if (expType == IDENTIFIER) {
        std::string currName = exp->getIdentifierName();
        return new IdentifierExp(currName == oldName ? newName : currName);
    } else if (expType == BINARY) {
        Expression* changedLhs = changeVariable(exp->getLhs(), oldName, newName);
        Expression* changedRhs = changeVariable(exp->getRhs(), oldName, newName);
        return new BinaryExp(exp->getOperator(), changedLhs, changedRhs);
    } else if (expType == UNARY) {
        Expression* changedOperand = changeVariable(exp->getRhs(), oldName, newName);
        return new UnaryExp(exp->getOperator(), changedOperand);
    } else {
        return new ConstantExp(exp->getConstantValue());
    }
}

void testChangeVariable() {
    cout << "---Change variable test---" << endl;
    EvaluationContext context;
    TokenScanner scanner;
    scanner.ignoreWhitespace();
    scanner.scanNumbers();

    Vector<std::string> expressions;
    expressions += "a = 3";
    expressions += "y = 5";
    expressions += "x = 42";
    expressions += "z = 3 * x * x - 4 * x - 2 * a + y";

    for (int i = 0; i < expressions.size(); i++) {
        Expression* exp = nullptr;

        try {
            scanner.setInput(expressions[i]);
            exp = parseExp(scanner);
            exp->eval(context);

            if (i == expressions.size() - 1) {
                cout << "Given: " << exp->toString() << endl << endl;
                cout << "change: 'x' to 't'" << endl << endl;

                Expression* newExpr = changeVariable(exp, "x", "t");

                cout << "new: " << newExpr->toString() << endl;
                cout << "old: " << exp->toString() << endl << endl;
                delete newExpr;
            }
        } catch (ErrorException& ex) {
            cerr << "Error: " << ex.getMessage() << endl;
        }

        if (exp != nullptr) delete exp;
    }
}

void listVariables(Expression* exp) {
    Set<string> variables;
    yieldVariables(exp, variables);

    for (string variable : variables) {
        cout << variable << endl;
    }
}

void yieldVariables(Expression* exp, Set<string>& variables) {
    if (exp->getType() == IDENTIFIER) {
        variables.add(exp->getIdentifierName());
    } else if (exp->getType() == BINARY) {
        yieldVariables(exp->getLhs(), variables);
        yieldVariables(exp->getRhs(), variables);
    } else if (exp->getType() == UNARY) {
        yieldVariables(exp->getRhs(), variables);
    }
}

bool expMatch(Expression* exp1, Expression* exp2) {
    ExpressionType exp1Type = exp1->getType();
    ExpressionType exp2Type = exp2->getType();

    if (exp1Type != exp2Type) return false;

    if (exp1Type == CONSTANT) return exp1->getConstantValue() == exp2->getConstantValue();

    if (exp1Type == IDENTIFIER) return exp1->getIdentifierName() == exp2->getIdentifierName();

    if (exp1Type == BINARY) {
        return exp1->getOperator() == exp2->getOperator()
               && expMatch(exp1->getLhs(), exp2->getLhs())
               && expMatch(exp1->getRhs(), exp2->getRhs());
    }

    if (exp1Type == UNARY) {
        return exp1->getOperator() == exp2->getOperator()
               && expMatch(exp1->getRhs(), exp1->getRhs());
    }

    return false;
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

Expression* createFromString(string exp) {
    TokenScanner scanner;
    scanner.ignoreWhitespace();
    scanner.scanNumbers();
    scanner.setInput(exp);
    return parseExp(scanner);
}

