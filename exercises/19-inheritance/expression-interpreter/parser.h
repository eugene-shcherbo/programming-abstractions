#ifndef PARSER_H
#define PARSER_H

#include "tokenscanner.h"
#include "exp.h"

Expression* parseExp(TokenScanner& scanner);
Expression* readE(TokenScanner& scanner, int prec);
Expression* readT(TokenScanner& scanner);

#endif // PARSER_H
