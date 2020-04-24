#include "numeric.h"
#include "strlib.h"

const std::string DIGITS = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const size_t MAX_BASE = DIGITS.size();
const int MIN_BASE = 2;

std::string numeric::integerToString(int val, int base) {
    if (base < MIN_BASE || static_cast<size_t>(base) > MAX_BASE) throw "base must be between 2 and 36";

    int quotient = abs(val);
    std::string res;

    while (quotient > 0) {
        res = DIGITS[static_cast<size_t>(quotient % base)] + res;
        quotient /= base;
    }
    return val >= 0 ? res : "-" + res;
}

int numeric::stringToInteger(std::string val, int base) {
    int res = 0;
    int pos = 0;

    for (int i = val.size() - 1; i >= 0; i--) {
        char digit = toUpperCase(val[i]);
        int num = 0;

        if (i == 0 && val[i] == '-') {
            res = -res;
        } else if (isalpha(digit)) {
            num = digit - 'A' + 10;
        } else if (isdigit(digit)) {
            num = digit - '0';
        } else {
            throw "stringToInteger: out of range";
        }

        if (num >= base) throw "stringToInteger: invalid input for specified base.";

        res += num * static_cast<int>(pow(base, pos));
        pos++;
    }

    return res;
}
