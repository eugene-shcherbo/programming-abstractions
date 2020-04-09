#ifndef _tokenscanner_h
#define _tokenscanner_h

#include <string>

class TokenScanner {
public:
    TokenScanner();
    TokenScanner(const std::string& source);

    void setSource(const std::string& source);
    bool hasMoreTokens();
    void ignoreWhiteSpaces();
    std::string nextToken();

private:
    std::string buffer;
    int pos;
    bool shouldIngoreWhiteSpaces;

    void skipWhitespaces();
};

#endif
