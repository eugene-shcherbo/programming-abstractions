#include <cctype>
#include "tokenscanner.h"

TokenScanner::TokenScanner() {
    pos = 0;
    buffer = "";
    shouldIngoreWhiteSpaces = false;
}

TokenScanner::TokenScanner(const std::string& source) {
    shouldIngoreWhiteSpaces = false;
    setSource(source);
}

void TokenScanner::setSource(const std::string& source) {
    pos = 0;
    buffer = source;
}

std::string TokenScanner::nextToken() {
    if (!hasMoreTokens()) {
        return "";
    } else if (isalnum(buffer[pos])) {
        int start = pos;
        while (pos < buffer.length() && isalnum(buffer[pos])) {
            pos++;
        }
        return buffer.substr(start, pos - start);
    } else {
        return std::string(1, buffer[pos++]);
    }
}

bool TokenScanner::hasMoreTokens() {
    if (shouldIngoreWhiteSpaces) {
        skipWhitespaces();
    }

    return pos < buffer.length();
}

void TokenScanner::ignoreWhiteSpaces() {
    shouldIngoreWhiteSpaces = true;
}

void TokenScanner::skipWhitespaces() {
    while (iswspace(buffer[pos])) {
        pos++;
    }
}
