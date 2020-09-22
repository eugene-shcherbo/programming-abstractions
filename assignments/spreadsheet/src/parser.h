/**
 * File: parser.h
 * --------------
 * This file acts as the interface to the parser module.
 */

#pragma once
#include <string>
#include "exp.h"
#include "tokenscanner.h"

class SSModel;

/**
 * Function: parseExp
 * Usage: Expression *exp = parseExp(scanner, spreadsheetModel);
 * -------------------------------------------
 * Parses a complete expression from the specified TokenScanner object,
 * making sure that there are no tokens left in the scanner at the end.
 */

Expression *parseExp(TokenScanner& scanner, const SSModel& spreadsheetModel);

