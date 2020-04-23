#include <cctype>
#include "tokenscanner.h"
#include "map.h"
#include "set.h"

enum State { S0, S1, S2, S3, S4, S5 };
bool isfinal(State st);

bool isquote(char ch);

namespace text {
    TokenScanner::TokenScanner() {
        shouldIngoreWhiteSpaces = false;
        shouldScanStringLiterals = false;
        shouldScanNumbers = false;
        setSource("");
    }

    TokenScanner::TokenScanner(const std::string& source) : TokenScanner() {
        setSource(source);
    }

    void TokenScanner::setSource(const std::string& source) {
        pos = 0;
        buffer = source;
    }

    std::string TokenScanner::nextToken() {
        if (!savedTokens.isEmpty()) {
            return savedTokens.pop();
        } else if (!hasMoreTokens()) {
            return "";
        } else if (isquote(buffer[pos]) && shouldScanStringLiterals) {
            return scanStringLiteral();
        } else if (isdigit(buffer[pos]) && shouldScanNumbers) {
            return scanNumber();
        } else if (isalnum(buffer[pos])) {
            return scanWord();
        }  else {
            return std::string(1, buffer[pos++]);
        }
    }

    bool TokenScanner::hasMoreTokens() {
        if (shouldIngoreWhiteSpaces) {
            skipWhitespaces();
        }

        return pos < buffer.length() || !savedTokens.isEmpty();
    }

    void TokenScanner::ignoreWhiteSpaces() {
        shouldIngoreWhiteSpaces = true;
    }

    void TokenScanner::scanString() {
        shouldScanStringLiterals = true;
    }

    void TokenScanner::scanNumbers() {
        shouldScanNumbers = true;
    }

    void TokenScanner::saveToken(std::string token) {
        savedTokens.push(token);
    }

    void TokenScanner::skipWhitespaces() {
        while (iswspace(buffer[pos])) {
            pos++;
        }
    }

    std::string TokenScanner::scanWord() {
        int start = pos;
        while (pos < buffer.length() && isalnum(buffer[pos])) {
            pos++;
        }
        return buffer.substr(start, pos - start);
    }

    std::string TokenScanner::scanStringLiteral() {
        int start = pos++;
        char quote = buffer[start];
        while (pos < buffer.length() && buffer[pos] != quote) {
            pos++;
        }
        pos++; // skip quotes, so that nextToken will start from the token after the quotes
        return buffer.substr(start, pos - start);
    }

    std::string TokenScanner::scanNumber() {
        std::string num;
        State currState = S0;

        while (pos < buffer.length()) {
            char ch = buffer[pos];

            switch (currState) {
                case S0:
                    if (isdigit(ch)) {
                        currState = S1;
                    }
                    break;
                case S1:
                    if (ch == '.') {
                        currState = S2;
                    } else if (ch == 'E') {
                        currState = S3;
                    } else if (!isdigit(ch)) {
                        return num;
                    }
                    break;
                case S2:
                    if (ch == 'E') {
                        currState = S3;
                    } else if (!isdigit(ch)) {
                        return num;
                    }
                    break;
                case S3:
                    if (ch == '+' || ch == '-') {
                        currState = S4;
                    } else if (isdigit(ch)) {
                        currState = S5;
                    } else {
                        throw "nextToken: wrong number format";
                    }
                    break;
                case S4:
                    if (isdigit(ch)) {
                        currState = S5;
                    } else {
                        throw "nextToken: wrong number format";
                    }
                    break;
                case S5:
                    if (!isdigit(ch)) {
                        return num;
                    }
                    break;
            }

            num += ch;
            pos++;
        }

        return num;
    }
}

bool isquote(char ch) {
    return ch == '\'' || ch == '"';
}

bool isfinal(State st) {
    return st == S1 || st == S2 || st == S5;
}
