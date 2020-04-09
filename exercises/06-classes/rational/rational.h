#ifndef _rational_h
#define _rational_h

#include <string>
#include <iostream>

class Rational {
public:
    Rational();
    Rational(int num);
    Rational(int n, int d);

    std::string toString() const;

    friend Rational operator+ (const Rational& r1, const Rational& r2);
    friend Rational operator* (const Rational& r1, const Rational& r2);
    friend Rational operator/ (const Rational& r1, const Rational& r2);
    friend Rational operator- (const Rational& r1, const Rational& r2);

private:
    int num;
    int den;

    void zero();
};

std::ostream& operator<< (std::ostream& os, const Rational& r);
Rational operator+ (const Rational& r1, const Rational& r2);
Rational operator* (const Rational& r1, const Rational& r2);
Rational operator/ (const Rational& r1, const Rational& r2);
Rational operator- (const Rational& r1, const Rational& r2);

#endif
