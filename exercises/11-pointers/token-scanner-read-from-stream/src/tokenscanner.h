#ifndef _tokenscanner_h
#define _tokenscanner_h

#include <string>
#include <istream>
#include "stack.h"

namespace text {
    class TokenScanner {
    public:
        TokenScanner();
        ~TokenScanner();
        TokenScanner(const std::string& source);

        void setSource(const std::string& source);
        void setSource(std::istream& source);
        bool hasMoreTokens();
        void ignoreWhiteSpaces();
        std::string nextToken();
        void saveToken(std::string token);
        void scanString();
        void scanNumbers();

    private:
        std::istream* buffer;
        bool shouldCleanMemory;
        bool shouldIngoreWhiteSpaces;
        bool shouldScanStringLiterals;
        bool shouldScanNumbers;
        Stack<std::string> savedTokens;

        void skipWhitespaces();
        std::string scanStringLiteral();
        std::string scanWord();
        std::string scanNumber();
        void clean();
    };
}

#endif
