#ifndef _bigint_h_
#define _bigint_h_

#include <string>

class BigInt {
public:
    BigInt(int val);
    BigInt(std::string digits);

    std::string toString() const;

    friend BigInt operator+(const BigInt& lop, const BigInt& rop);
    friend BigInt operator*(const BigInt& lop, const BigInt& rop);

private:
    struct Node {
        int digit;
        Node* next;
    };

    Node* digits_;
    int numDigits_;

    std::string toString(Node* node) const;
};

BigInt operator+(const BigInt& lop, const BigInt& rop);
BigInt operator*(const BigInt& lop, const BigInt& rop);

#endif
