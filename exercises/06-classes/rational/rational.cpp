#include <cstdlib>
#include <sstream>
#include "rational.h"

int gcd(int x, int y);
std::string integerToString(int val);

Rational::Rational() {
    zero();
}

Rational::Rational(int n) {
    num = n;
    den = 1;
}

Rational::Rational(int n, int d) {
    if (d == 0) {
        throw "rational ctor: denumenator can't be 0";
    } else if (n == 0) {
        zero();
    } else {
        int g = gcd(std::abs(n), std::abs(d));
        num = n / g;
        den = std::abs(d) / g;

        if (d < 0) {
            num = -num;
        }
    }
}

std::ostream& operator<< (std::ostream& os, const Rational& r) {
    return os << r.toString();
}

Rational operator+ (const Rational& r1, const Rational& r2) {
    return Rational(r1.num * r2.den + r2.num * r1.den, r1.den * r2.den);
}

Rational operator* (const Rational& r1, const Rational& r2) {
    return Rational(r1.num * r2.num, r1.den * r2.den);
}

Rational operator/ (const Rational& r1, const Rational& r2) {
    return Rational(r1.num * r2.den, r1.den * r2.num);
}

Rational operator- (const Rational& r1, const Rational& r2) {
    return Rational(r1.num * r2.den - r2.num * r1.den, r1.den * r2.den);
}

std::string Rational::toString() const {
    if (den == 1) {
        return integerToString(num);
    } else {
        return integerToString(num) + "/" + integerToString(den);
    }
}

void Rational::zero() {
    num = 0;
    den = 1;
}

int gcd(int x, int y) {
    int r = x % y;

    while (r != 0) {
        x = y;
        y = r;
        r = x % y;
    }

    return y;
}

std::string integerToString(int val) {
    std::ostringstream os;
    os << val;
    return os.str();
}
