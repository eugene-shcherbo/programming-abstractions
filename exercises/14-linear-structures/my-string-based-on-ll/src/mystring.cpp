#include <ostream>
#include "error.h"
#include "mystring.h"

MyString::MyString(std::string str) {
    size_ = str.length();
    chars_ = nullptr;
    Cell* tail = nullptr;
    for (unsigned long i = 0; i < size_; i++) {
        Cell* newNode = new Cell { str[i], nullptr };
        if (tail == nullptr) {
            chars_ = newNode;
        } else {
            tail->next = newNode;
        }
        tail = newNode;
    }
}

MyString::MyString(const MyString& other) {
    deepCopy(other);
}

MyString::~MyString() {
    clear();
}

std::string MyString::toString() const {
    std::string str;

    for (Cell* curr = chars_; curr != nullptr; curr = curr->next) {
        str += curr->ch;
    }

    return str;
}

unsigned long MyString::length() const {
    return size_;
}

MyString MyString::substr(unsigned long start, unsigned long n) const {
    if (start >= size_) {
        error("substr: the start index is outside the string");
    }

    Cell* from = chars_;
    for (unsigned long i = 0; i < start; i++) {
        from = from->next;
    }

    std::string str;
    unsigned long num = 0;
    while (from != nullptr && num < n) {
        str += from->ch;
        from = from->next;
        num++;
    }

    return MyString(str);
}

MyString MyString::substr(unsigned long start) const {
    return substr(start, size_);
}

void MyString::deepCopy(const MyString& str) {
    size_ = str.size_;
    Cell* tail = nullptr;
    for (Cell* curr = str.chars_; curr != nullptr; curr = curr->next) {
        Cell* newNode = new Cell { curr->ch, nullptr };
        if (tail == nullptr) {
            chars_ = newNode;
        } else {
            tail->next = newNode;
        }
        tail = newNode;
    }
}

void MyString::clear() {
    for (unsigned long i = 0; i < length(); i++) {
        Cell* old = chars_;
        chars_ = chars_->next;
        delete old;
    }
}

char& MyString::operator[](unsigned long pos) {
    if (pos > size_) {
        error("error: the pos is outside the string");
    }
    Cell* res = chars_;
    for (unsigned long i = 0; i < pos; i++) {
        res = res->next;
    }
    return res->ch;
}

char MyString::operator[](unsigned long pos) const {
    if (pos > size_) {
        error("error: the pos is outside the string");
    }
    Cell* res = chars_;
    for (unsigned long i = 0; i < pos; i++) {
        res = res->next;
    }
    return res->ch;
}

MyString& MyString::operator=(const MyString& other) {
    if (this != &other) {
        clear();
        deepCopy(other);
    }
    return *this;
}

std::ostream& operator<<(std::ostream& os, const MyString& str) {
    for (MyString::Cell* curr = str.chars_; curr != nullptr; curr = curr->next) {
        os << curr->ch;
    }
    return os;
}

MyString operator+(const MyString& lstr, const MyString& rstr) {
    MyString str(lstr);
    return str += rstr;
}

MyString& operator+=(MyString& lstr, const MyString& rstr) {
    MyString::Cell* tail = lstr.chars_;
    while (tail->next != nullptr) {
        tail = tail->next;
    }

    // Two strings might be identical, so we want to ensure
    // therefore we want to concatanate a string only rstr.length()
    // otherwise curr != nullptr will be always false (because we always append into the end)
    MyString::Cell* curr = rstr.chars_;
    for (unsigned long i = 0; i < rstr.length(); i++) {
        MyString::Cell* newNode = new MyString::Cell { curr->ch, nullptr };
        tail->next = newNode;
        tail = newNode;
        curr = curr->next;
    }
    lstr.size_ += rstr.size_;
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
