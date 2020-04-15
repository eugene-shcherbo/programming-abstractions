
/*
 * File: Main.cpp
 * -----------------------
 * This program simulates an electronic calculator that uses
 * reverse Polish notation, in which operators come after
 * the operands to which they apply. Information for users
 * of this application appears in the helpCommand function.
 */

#include <iostream>
#include <cctype>
#include "stack.h"
#include "console.h"
#include "strlib.h"
#include "simpio.h"
#include "rational.h"
using namespace std;

/*
 * Function: applyOperator
 * Usage: applyOperator(op, operandStack);
 * ---------------------------------------
 * This function applies the operator to the top two elements on
 * the operand stack. Because the elements on the stack are
 * popped in reverse order, the right operand is popped before
 * the left operand.
 */

void applyOperator(char op, Stack<Rational>& operandStack);

/*
 * Function: helpCommand
 * Usage: helpCommand();
 * ---------------------
 * This function generates a help message for the user.
 */

void helpCommand();

int main() {
    cout << "RPN Calculator Simulation (type H for help)" << endl;

    Stack<Rational> operandStack;

    while (true) {
        string line = getLine("> ");

        if (line.empty()) {
            break;
        }

        char ch = toupper(line[0]);

        if (ch == 'Q') {
            break;
        } else if (ch == 'C') {
            operandStack.clear();
        } else if (ch == 'H') {
            helpCommand();
        } else if (isdigit(ch)) {
            operandStack.push(stringToInteger(line));
        } else {
            applyOperator(ch, operandStack);
        }
    }

    return 0;
}

void applyOperator(char op, Stack<Rational>& operandStack) {
    Rational result = 0;
    Rational rhs = operandStack.pop();
    Rational lhs = operandStack.pop();

    switch (op) {
        case '+':
            result = lhs + rhs;
            break;
        case '-':
            result = lhs - rhs;
            break;
        case '*':
            result = lhs * rhs;
            break;
        case '/':
            result = lhs / rhs;
            break;
        default:
            error("Illegal operator");
    }

    cout << result << endl;
    operandStack.push(result);
}

void helpCommand() {
    cout << "Enter expressions in Reverse Polish Notation," << endl
         << "in which operators follow the operands to which" << endl
         << "they apply. Each line consits of a number, an" << endl
         << "operator, or one of the following commands:" << endl
         << "   Q -- Quit the program" << endl
         << "   H -- Display this help message" << endl
         << "   C -- Clear the calculator stack" << endl;
}


