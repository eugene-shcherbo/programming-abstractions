#include <cmath>
#include "strlib.h"
#include "bigint.h"

BigInt::BigInt(int val) {
    digits_ = nullptr;
    Node* tail = nullptr;
    numDigits_ = val == 0 ? 1 : 0;

    while (val > 0) {
        Node* newNode = new Node { val % 10, nullptr };
        if (tail == nullptr) {
            digits_ = newNode;
        } else {
            tail->next = newNode;
        }
        tail = newNode;
        val /= 10;
        numDigits_++;
    }
}

BigInt::BigInt(std::string digits) {
    digits_ = nullptr;
    Node* tail = nullptr;
    numDigits_ = digits.length();

    for (int i = digits.length() - 1; i >= 0; i--) {
        Node* newNode = new Node { digits[i] - '0', nullptr };
        if (tail == nullptr) {
            digits_ = newNode;
        } else {
            tail->next = newNode;
        }
        tail = newNode;
    }
}

std::string BigInt::toString() const {
    if (digits_ == nullptr) {
        return "0";
    }
    return toString(digits_);
}

BigInt operator+(const BigInt& lop, const BigInt& rop) {
    BigInt::Node* left = lop.numDigits_ > rop.numDigits_ ? lop.digits_ : rop.digits_;
    BigInt::Node* right = lop.numDigits_ <= rop.numDigits_ ? lop.digits_ : rop.digits_;

    BigInt res(0);
    res.numDigits_ = 0;
    BigInt::Node* tail = nullptr;
    int carry = 0;

    while (right != nullptr) {
        int sum = left->digit + right->digit + carry;
        carry = sum / 10;
        BigInt::Node* newNode = new BigInt::Node{ sum % 10, nullptr };

        if (tail == nullptr) {
            res.digits_ = newNode;
        } else {
            tail->next = newNode;
        }

        tail = newNode;
        left = left->next;
        right = right->next;
        res.numDigits_++;
    }

    while (left != nullptr) {
        int sum = left->digit + carry;
        carry = sum / 10;
        BigInt::Node* newNode = new BigInt::Node{ sum % 10, nullptr };

        if (tail == nullptr) {
            res.digits_ = newNode;
        } else {
            tail->next = newNode;
        }
        tail = newNode;
        res.numDigits_++;

        if (left->next == nullptr && carry > 0) {
            newNode = new BigInt::Node { carry, nullptr };
            tail->next = newNode;
            tail = newNode;
            res.numDigits_++;
            carry = 0;
        }
        left = left->next;
    }

    if (carry > 0) {
        BigInt::Node* newNode = new BigInt::Node { carry, nullptr };
        tail->next = newNode;
        tail = newNode;
        res.numDigits_++;
        carry = 0;
    }

    return res;

}

BigInt operator*(const BigInt& lop, const BigInt& rop) {
    BigInt res(0);

    if (lop.numDigits_ <= 1) {
        if (lop.digits_ != nullptr) {
            for (int i = 0; i < lop.digits_->digit; i++) {
                res = res + rop;
            }
        }
    } else {
        BigInt rest(0);
        rest.numDigits_ = lop.numDigits_ - 1;
        BigInt::Node* tail = nullptr;
        for (BigInt::Node* curr = lop.digits_->next; curr != nullptr; curr = curr->next) {
            BigInt::Node* newNode = new BigInt::Node { curr->digit, nullptr };
            if (tail == nullptr) {
                rest.digits_ = newNode;
            } else {
                tail->next = newNode;
            }
            tail = newNode;
        }

        BigInt left = BigInt(lop.digits_->digit) * rop;
        BigInt rightTmp = rest * rop;
        BigInt right(0);

        for (int i = 0; i < 10; i++) {
            right = right + rightTmp;
        }

        return left + right;

    }

    return res;
}

std::string BigInt::toString(Node* node) const {
    if (node != nullptr) {
        return toString(node->next) + char(node->digit + '0');
    }
    return "";
}
