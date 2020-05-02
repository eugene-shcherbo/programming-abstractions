#include <ostream>
#include "mystring.h"

MyString::MyString(std::string str) {
    size_ = str.length();
    chars_ = new char[size_];

    for (unsigned long i = 0; i < size_; i++) {
        chars_[i] = str[i];
    }
}

MyString::MyString(const MyString& other) {
    deepCopy(other);
}

MyString::~MyString() {
    delete[] chars_;
}

std::string MyString::toString() const {
    std::string str;

    for (unsigned long i = 0; i < size_; i++) {
        str += chars_[i];
    }

    return str;
}

unsigned long MyString::length() const {
    return size_;
}

MyString MyString::substr(unsigned long start, unsigned long n) const {
    if (start >= size_) {
        throw "substr: the start index is outside the string";
    }

    std::string str;

    unsigned long num = 0;
    for (unsigned long i = start; num < n && i < size_; i++, num++) {
        str += chars_[i];
    }

    return MyString(str);
}

MyString MyString::substr(unsigned long start) const {
    return substr(start, size_);
}

char& MyString::operator[](unsigned long pos) {
    if (pos > size_) {
        throw "error: the pos is outside the string";
    }
    return chars_[pos];
}

char MyString::operator[](unsigned long pos) const {
    if (pos > size_) {
        throw  "error: the pos is outside the string";
    }
    return chars_[pos];
}

MyString& MyString::operator=(const MyString& other) {
    if (this != &other) {
        delete[] chars_;
        deepCopy(other);
    }
    return *this;
}

void MyString::deepCopy(const MyString& str) {
    size_ = str.size_;
    chars_ = new char[size_];

    for (unsigned long i = 0; i < size_; i++) {
        chars_[i] = str.chars_[i];
    }
}

std::ostream& operator<<(std::ostream& os, const MyString& str) {
    for (unsigned long i = 0; i < str.size_; i++) {
        os << str.chars_[i];
    }
    return os;
}

MyString operator+(const MyString& lstr, const MyString& rstr) {
    MyString str(lstr);
    return str += rstr;
}

MyString& operator+=(MyString& lstr, const MyString& rstr) {
    char* old = lstr.chars_;
    lstr.chars_ = new char[lstr.size_ + rstr.size_];

    for (unsigned long i = 0; i < lstr.size_; i++) {
        lstr[i] = old[i];
    }

    for (unsigned long i = 0; i < rstr.size_; i++) {
        lstr.chars_[i + lstr.size_] = rstr.chars_[i];
    }

    lstr.size_ += rstr.size_;
    delete [] old;

    return lstr;
}

bool operator==(const MyString& lstr, const MyString& rstr) {
    if (lstr.length() != rstr.length()) {
        return false;
    }

    for (unsigned long i = 0; i < lstr.length(); i++) {
        if (lstr[i] != rstr[i]) {
            return false;
        }
    }

    return true;
}

bool operator!=(const MyString& lstr, const MyString& rstr) {
    return !(lstr == rstr);
}

bool operator<=(const MyString& lstr, const MyString& rstr) {
    return !(lstr > rstr);
}

bool operator>=(const MyString& lstr, const MyString& rstr) {
    return !(lstr < rstr);
}

bool operator>(const MyString& lstr, const MyString& rstr) {
    return rstr < lstr;
}

bool operator<(const MyString& lstr, const MyString& rstr) {
    if (lstr.length() == 0 && rstr.length() > 0) {
        return true;
    }

    for (unsigned long i = 0; i < lstr.length() && i < rstr.length(); i++) {
        if (lstr[i] > rstr[i]) {
            return true;
        }
    }

    return false;
}
