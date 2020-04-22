#ifndef _tokenscanner_h
#define _tokenscanner_h

#include <string>
#include "stack.h"

namespace text {
    class TokenScanner {
    public:
        TokenScanner();
        TokenScanner(const std::string& source);

        void setSource(const std::string& source);
        bool hasMoreTokens();
        void ignoreWhiteSpaces();
        std::string nextToken();
        void saveToken(std::string token);

    private:
        std::string buffer;
        int pos;
        bool shouldIngoreWhiteSpaces;
        Stack<std::string> savedTokens;

        void skipWhitespaces();
    };
}

#endif
