#include <iostream>
#include <string>
#include "tokenscanner.h"
#include "strlib.h"
#include "error.h"
#include "exp.h"
#include "parser.h"

Expression* parseExp(TokenScanner& scanner) {
    Expression* exp = readE(scanner, 0);
    if (scanner.hasMoreTokens()) {
        error("Unexpected token \"" + scanner.nextToken() + "\"");
    }
    return exp;
}

Expression* readE(TokenScanner& scanner, int prec) {
    Expression* exp = readT(scanner);
    std::string token;
    while (true) {
        token = scanner.nextToken();
        int tPrec = calcPrecedence(token);
        if (tPrec <= prec) break;
        Expression* rhs = readE(scanner, tPrec);
        exp = new BinaryExp(token, exp, rhs);
    }
    scanner.saveToken(token);
    return exp;
}

Expression* readT(TokenScanner& scanner) {
    std::string token = scanner.nextToken();
    TokenScanner::TokenType type = scanner.getTokenType(token);
    if (type == TokenScanner::WORD) return new IdentifierExp(token);
    if (type == TokenScanner::NUMBER) return new ConstantExp(stringToDouble(token));

    if (token == "-") {
        Expression* operand = readT(scanner);
        return new UnaryExp(token, operand);
    }

    if (token != "(") error("Illegal term in expression");
    Expression* exp = readE(scanner, 0);
    if (scanner.nextToken() != ")") {
        error("Unbalanced parentheses in expression");
    }
    return exp;
}

int calcPrecedence(std::string op) {
    if (op == "=") return 1;
    if (op == "+" || op == "-") return 2;
    if (op == "*" || op == "/" || op == "%") return 3;
    return 0;
}
