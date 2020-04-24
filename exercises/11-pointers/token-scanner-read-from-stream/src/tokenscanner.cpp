#include <cctype>
#include <sstream>
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
        shouldCleanMemory = false;
        setSource("");
    }

    TokenScanner::TokenScanner(const std::string& source) : TokenScanner() {
        setSource(source);
    }

    TokenScanner::~TokenScanner() {
        clean();
    }

    void TokenScanner::setSource(const std::string& source) {
        clean();
        buffer = new std::istringstream(source);
        shouldCleanMemory = true;
    }

    void TokenScanner::setSource(std::istream& source) {
        clean();
        buffer = &source;
    }

    std::string TokenScanner::nextToken() {
        char ch;
        buffer->get(ch);

        if (!savedTokens.isEmpty()) {
            return savedTokens.pop();
        } else if (!hasMoreTokens()) {
            return "";
        } else if (isquote(ch) && shouldScanStringLiterals) {
            return scanStringLiteral();
        } else if (isdigit(ch) && shouldScanNumbers) {
            return scanNumber();
        } else if (isalnum(ch)) {
            return scanWord();
        }  else {
            return std::string(1, ch);
        }
    }

    bool TokenScanner::hasMoreTokens() {
        if (shouldIngoreWhiteSpaces) {
            skipWhitespaces();
        }

        return buffer->peek() != EOF || !savedTokens.isEmpty();
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
        char ch;
        while ((*buffer) >> ch && iswspace(ch));
        buffer->unget();
    }

    std::string TokenScanner::scanWord() {
        buffer->unget();
        std::string word;
        char ch;
        while (buffer->get(ch) && isalnum(ch)) {
            word += ch;
        }
        buffer->unget();
        return word;
    }

    std::string TokenScanner::scanStringLiteral() {
        buffer->unget();
        char quotes;
        buffer->get(quotes);
        std::string str = std::string(1, quotes);
        char ch;
        while (buffer->get(ch) && ch != quotes) {
            str += ch;
        }
        return str + quotes;
    }

    std::string TokenScanner::scanNumber() {
        buffer->unget();
        std::string num;
        State currState = S0;
        char ch;

        while (buffer->get(ch)) {
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
                        buffer->unget();
                        return num;
                    }
                    break;
                case S2:
                    if (ch == 'E') {
                        currState = S3;
                    } else if (!isdigit(ch)) {
                        buffer->unget();
                        return num;
                    }
                    break;
                case S3:
                    if (ch == '+' || ch == '-') {
                        currState = S4;
                    } else if (isdigit(ch)) {
                        currState = S5;
                    } else {
                        buffer->unget();
                        throw "nextToken: wrong number format";
                    }
                    break;
                case S4:
                    if (isdigit(ch)) {
                        currState = S5;
                    } else {
                        buffer->unget();
                        throw "nextToken: wrong number format";
                    }
                    break;
                case S5:
                    if (!isdigit(ch)) {
                        buffer->unget();
                        return num;
                    }
                    break;
            }

            num += ch;
        }

        return num;
    }

    void TokenScanner::clean() {
        if (shouldCleanMemory) {
            delete buffer;
            shouldCleanMemory = false;
        }
    }
}

bool isquote(char ch) {
    return ch == '\'' || ch == '"';
}

bool isfinal(State st) {
    return st == S1 || st == S2 || st == S5;
}
