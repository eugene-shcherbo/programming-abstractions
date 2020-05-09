#include <iostream>
#include <iomanip>
#include <string>
#include "console.h"
#include "strlib.h"
#include "bigint.h"
using namespace std;

int main() {
    BigInt zero(0);
    cout << "zero=" << zero.toString() << endl;

    BigInt ten(10);
    cout << "ten=" << ten.toString() << endl;

    BigInt hundredThousandFiveHundred("100500");
    cout << "one hundred thousand five hundred=" << hundredThousandFiveHundred.toString() << endl;

    BigInt sum = ten + hundredThousandFiveHundred;
    cout << "sum=" << sum.toString() << endl;

    cout << "990 + 10 = " << (BigInt(990) + BigInt(10)).toString() << endl;
    cout << "10 * 10 = " << (BigInt(10) * BigInt(10)).toString() << endl;
    cout << "0 + 10 = " << (BigInt(0) + BigInt(10)).toString() << endl;
    cout << "90 + 10 = " << (BigInt(90) + BigInt(10)).toString() << endl;
    cout << "120 * 6 = " << (BigInt(120) * BigInt(6)).toString() << endl;

    cout << endl << "---- Factorial table -----" << endl;
    BigInt fact(1);
    for (int i = 1; i <= 52; i++) {
        fact = fact * i;
        cout << setw(4) << i << "th" << std::setw(fact.toString().length() + 5) << fact.toString() << endl;
    }

    return 0;
}
