/*
 * File: parser.cpp
 * ----------------
 * This file implements the parser.h interface.
 */

#include <iostream>
#include <string>
#include "error.h"
#include "exp.h"
#include "parser.h"
#include "strlib.h"
#include "tokenscanner.h"
#include "ssmodel.h"
#include "ssutil.h"
using namespace std;

static Expression *readE(TokenScanner& scanner, const SSModel& spreadsheetModel, int prec = 0);
static Expression *readT(TokenScanner& scanner, const SSModel& spreadsheetModel);
static bool isFunction(const std::string& token);
static Expression* parseFunction(const std::string& funcName, TokenScanner& scanner, const SSModel& spreadsheetModel);
static Range readRange(TokenScanner& scanner, const SSModel& spreadsheetModel);
static std::string readCellName(TokenScanner& scanner, const SSModel& spreadsheetModel);
static int precedence(const std::string& token);

/**
 * Implementation notes: parseExp
 * ------------------------------
 * This code just reads an expression and then checks for extra tokens.
 */

Expression *parseExp(TokenScanner& scanner, const SSModel& spreadsheetModel) {
   Expression *exp = readE(scanner, spreadsheetModel);
   if (scanner.hasMoreTokens()) {
      error("Unexpected token \"" + scanner.nextToken() + "\"");
   }
   return exp;
}

/**
 * Implementation notes: readE
 * Usage: exp = readE(scanner, prec);
 * ----------------------------------
 * The implementation of readE uses precedence to resolve the ambiguity in
 * the grammar.  At each level, the parser reads operators and subexpressions
 * until it finds an operator whose precedence is greater than the prevailing
 * one.  When a higher-precedence operator is found, readE calls itself
 * recursively to read that subexpression as a unit.
 */

Expression *readE(TokenScanner& scanner, const SSModel& spreadsheetModel, int prec) {
   Expression *exp = readT(scanner, spreadsheetModel);
   string token;
   while (true) {
      token = scanner.nextToken();
      int tprec = precedence(token);
      if (tprec <= prec) break;
      Expression *rhs = readE(scanner, spreadsheetModel, tprec);
      exp = new CompoundExp(token, exp, rhs);
   }
   scanner.saveToken(token);
   return exp;
}

/**
 * Implementation notes: readT
 * ---------------------------
 * This function scans a term, which is either an integer, an identifier,
 * or a parenthesized subexpression.
 */
Expression *readT(TokenScanner& scanner, const SSModel& spreadsheetModel) {
   string token = scanner.nextToken();
   TokenScanner::TokenType type = scanner.getTokenType(token);
   if (isFunction(token)) return parseFunction(token, scanner, spreadsheetModel);
   if (type == TokenScanner::WORD) return new IdentifierExp(token);
   if (type == TokenScanner::NUMBER) return new DoubleExp(stringToReal(token));
   if (type == TokenScanner::STRING) return new TextStringExp(token.substr(1, token.length() - 2));
   if (token != "(") error("Unexpected token \"" + token + "\"");
   Expression *exp = readE(scanner, spreadsheetModel, 0);
   if (scanner.nextToken() != ")") {
      error("Unbalanced parentheses");
   }
   return exp;
}

static bool isFunction(const std::string& token) {
    return supportRangeFunction(token);
}

static Expression* parseFunction(const std::string& funcName, TokenScanner& scanner, const SSModel& spreadsheetModel) {
    string token = scanner.nextToken();
    if (token != "(") error("Expected parenthesis before cell name");
    Range cellRange = readRange(scanner, spreadsheetModel);
    token = scanner.nextToken();
    if (token != ")") error("Expected parethesis after cell name");
    return new FunctionExpression(funcName, getRangeFunction(funcName), cellRange);
}

static Range readRange(TokenScanner& scanner, const SSModel& spreadsheetModel) {
    std::string leftCorner = readCellName(scanner, spreadsheetModel);
    std::string token = scanner.nextToken();
    if (token != ":") error("Expected ':' after " + leftCorner);
    std::string rightCorner = readCellName(scanner, spreadsheetModel);
    return Range(leftCorner, rightCorner, spreadsheetModel.lastColName(), spreadsheetModel.lastRowNum());
}

static std::string readCellName(TokenScanner& scanner, const SSModel& spreadsheetModel) {
    std::string token = scanner.nextToken();
    if (!spreadsheetModel.nameIsValid(token)) error("Cell name is invalid");
    return token;
}

/**
 * Implementation notes: precedence
 * --------------------------------
 * This function checks the token against each of the defined operators
 * and returns the appropriate precedence value.
 */
int precedence(const string& token) {
   if (token == "+" || token == "-") return 1;
   if (token == "*" || token == "/") return 2;
   return 0;
}
