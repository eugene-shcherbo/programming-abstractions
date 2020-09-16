#include <iostream>
#include <string>
#include "tokenscanner.h"
#include "strlib.h"
#include "error.h"
#include "exp.h"
#include "parser.h"

Line* readLine(TokenScanner& scanner) {
    std::string token = scanner.nextToken();

    if (scanner.getTokenType(token) != TokenScanner::NUMBER) {
        error("Unexpected token \"" + token + "\"");
    }

    Statement* stm = readStatement(scanner);
    int number = stringToInteger(token);

    if (scanner.hasMoreTokens()) {
        error("Unexpected token \"" + scanner.nextToken() + "\"");
    }

    return Line::create(static_cast<uint>(number), stm);
}

Statement* readStatement(TokenScanner& scanner)  {
    std::string token = scanner.nextToken();
    Statement* stm = nullptr;

    if (token == "LET") {
        Expression* assignExpr = parseExp(scanner);
        stm = Statement::let(assignExpr->getLhs()->getIdentifierName(), assignExpr);
    } else if (token == "PRINT") {
        std::string varName = scanner.nextToken();
        stm = Statement::print(varName, std::cout);
    } else if (token == "IF") {
        Expression* lhs = readE(scanner, 0);
        std::string op = scanner.nextToken();
        Expression* rhs = readE(scanner, 0);

        token = scanner.nextToken();

        if (token != "THEN") {
            error("Unexpected token \"" + token + "\"");
        }

        token = scanner.nextToken();

        if (scanner.getTokenType(token) != TokenScanner::NUMBER) {
            error("Unexpected token \"" + token + "\"");
        }

        stm = Statement::ifThen(op, lhs, rhs, stringToInteger(token));
    }

    return stm;
}

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
