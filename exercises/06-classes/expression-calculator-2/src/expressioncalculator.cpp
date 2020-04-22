#include "expressioncalculator.h"
#include "tokenscanner.h"
#include "strlib.h"

std::string concatRemaining(TokenScanner& scanner);

double ExpressionCalculator::evaluate(std::string statement) {
    TokenScanner scanner(statement);
    scanner.ignoreWhitespace();
    scanner.scanNumbers();

    if (!scanner.hasMoreTokens()) {
        return .0;
    }

    std::string lOperand = scanner.nextToken();

    while (scanner.hasMoreTokens()) {
        std::string op = scanner.nextToken();
        std::string rOperand = scanner.nextToken();
        double evalRes = .0;

        if (op[0] == '=') {
            evalRes = assignVariable(lOperand, rOperand + concatRemaining(scanner));
        } else {
            evalRes = calc(op, lOperand, rOperand);
        }

        lOperand = realToString(evalRes);
    }

    return getVariableOrValue(lOperand);
}

double ExpressionCalculator::assignVariable(std::string name, std::string expression) {
    double res = evaluate(expression);

    if (variables.containsKey(name)) {
        variables[name] = res;
    } else {
        variables.add(name, res);
    }

    return res;
}

double ExpressionCalculator::calc(std::string op, std::string lOperand, std::string rOperand) {
    double lop = getVariableOrValue(lOperand);
    double rop = getVariableOrValue(rOperand);

    switch (op[0]) {
        case '+':
            return lop + rop;
        case '-':
            return lop - rop;
        case '/':
            return lop / rop;
        case '*':
            return lop * rop;
    }

    return lop;
}

double ExpressionCalculator::getVariableOrValue(std::string operand) {
    if (variables.containsKey(operand)) {
        return variables[operand];
    } else {
        return stringToReal(operand);
    }
}

std::string concatRemaining(TokenScanner& scanner) {
    std::string res;

    while (scanner.hasMoreTokens()) {
        res += scanner.nextToken();
    }

    return res;
}
