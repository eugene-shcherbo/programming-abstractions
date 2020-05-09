
#ifndef _mystring_h_
#define _mystring_h_

#include <string>

class MyString {
public:
    MyString(std::string str);
    MyString(const MyString& other);
    ~MyString();

    std::string toString() const;
    unsigned long length() const;
    MyString substr(unsigned long start, unsigned long n) const;
    MyString substr(unsigned long start) const;

    char& operator[](unsigned long pos);
    char operator[](unsigned long pos) const;
    MyString& operator=(const MyString& other);

    friend std::ostream& operator<<(std::ostream& os, const MyString& str);
    friend MyString& operator+=(MyString& lstr, const MyString& rstr);

private:
    struct Cell {
        char ch;
        Cell* next;
    };

    Cell* chars_;
    unsigned long size_;

    void clear();
    void deepCopy(const MyString& str);
    void extendCapacity();
};

MyString operator+(const MyString& lstr, const MyString& rstr);
MyString& operator+=(MyString& lstr, const MyString& rstr);
std::ostream& operator<<(std::ostream& os, const MyString& str);
bool operator==(const MyString& lstr, const MyString& rstr);
bool operator!=(const MyString& lstr, const MyString& rstr);
bool operator<=(const MyString& lstr, const MyString& rstr);
bool operator>=(const MyString& lstr, const MyString& rstr);
bool operator>(const MyString& lstr, const MyString& rstr);
bool operator<(const MyString& lstr, const MyString& rstr);

#endif
