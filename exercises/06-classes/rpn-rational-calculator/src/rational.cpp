#include <cstdlib>
#include <sstream>
#include "strlib.h"
#include "rational.h"

int gcd(int x, int y);

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

bool operator== (const Rational& r1, const Rational& r2) {
    return r1.den == r2.den && r1.num == r2.num;
}

bool operator!= (const Rational& r1, const Rational& r2) {
    return !(r1 == r2);
}

bool operator< (const Rational& r1, const Rational& r2) {
    return !(r1 >= r2);
}

bool operator<= (const Rational& r1, const Rational& r2) {
    return r1 < r2 || r1 == r2;
}

bool operator> (const Rational& r1, const Rational& r2) {
    return (r1 - r2).num > 0;
}

bool operator>= (const Rational& r1, const Rational& r2) {
    return r1 > r2 || r1 == r2;
}

Rational operator+= (Rational& r1, const Rational& r2) {
    r1 = r1 + r2;
    return r1;
}

Rational operator*= (Rational& r1, const Rational& r2) {
    r1 = r1 * r2;
    return r1;
}

Rational operator/= (Rational& r1, const Rational& r2) {
    r1 = r1 / r2;
    return r1;
}

Rational operator-= (Rational& r1, const Rational& r2) {
    r1 = r1 - r2;
    return r1;
}

Rational operator++ (Rational& r, int) {
    Rational old = r;
    r += 1; // implicit conversion via constructor Rational(int n)s
    return old;
}

Rational operator++ (Rational& r) {
    return r += 1;
}

Rational operator-- (Rational& r, int) {
    Rational old = r;
    r -= 1;
    return old;
}

Rational operator-- (Rational& r) {
    return r -= 1;
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
