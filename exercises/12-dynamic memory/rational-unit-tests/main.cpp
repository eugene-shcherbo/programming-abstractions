#include <iostream>
#include <cassert>
#include "rational.h"

using namespace std;

void testConstructors();
void testAriphmeticOperators();
void testRelationsOperators();

int main() {
    testConstructors();
    testAriphmeticOperators();
    testRelationsOperators();

    return 0;
}

void testConstructors() {
    assert(Rational().toString() == "0");
    assert(Rational(5).toString() == "5");
    assert(Rational(1, 3).toString() == "1/3");
    assert(Rational(2, 6).toString() == "1/3");
    assert(Rational(-1, 3).toString() == "-1/3");
    assert(Rational(-1, -3).toString() == "1/3");
}

void testAriphmeticOperators() {
    Rational oneThird(1, 3);
    Rational oneSix(1, 6);
    Rational threeSix(3, 6);

    assert((oneThird + 1).toString() == "4/3");
    assert((oneThird + oneThird).toString() == "2/3");
    assert((oneThird + oneSix).toString() == "1/2");
    assert((threeSix + threeSix).toString() == "1");

    assert((oneThird * 2).toString() == "2/3");
    assert((oneThird * oneThird).toString() == "1/9");
    assert((oneThird * oneSix).toString() == "1/18");
    assert((threeSix * threeSix).toString() == "1/4");

    assert((oneThird - 1).toString() == "-2/3");
    assert((oneThird - oneThird).toString() == "0");
    assert((oneThird - oneSix).toString() == "1/6");

    assert((oneThird / 2).toString() == "1/6");
    assert((oneThird / oneThird).toString() == "1");
    assert((oneThird / oneSix).toString() == "2");
}

void testRelationsOperators() {
    assert(Rational(2, 6) == Rational(1, 3));
    assert(Rational(1, 3) > Rational(1, 6));
    assert(Rational(-1) < Rational());
}
