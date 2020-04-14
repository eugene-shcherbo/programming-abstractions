//
//  calendar.hpp
//  calendar
//
//  Created by Eugene Shcherbo on 9/22/19.
//  Copyright © 2019 Eugene Shcherbo. All rights reserved.
//

#ifndef calendar_hpp
#define calendar_hpp

#include <string>

enum Month {
    JANUARY = 1,
    FEBRUARY,
    MARCH,
    APRIL,
    MAY,
    JUNE,
    JULY,
    AUGUST,
    SEPTEMBER,
    OCTOBER,
    NOVEMBER,
    DECEMBER
};

class Date {
public:
    Date();
    Date(Month m, int d, int y);
    Date(int d, Month m, int y);
    
    int getDay() const;
    Month getMonth() const;
    int getYear() const;
    
    std::string toString() const;
private:
    Month month;
    int day;
    int year;
};

std::ostream& operator<< (std::ostream& os, const Date& d);

/* Operators */
bool operator== (const Date& d1, const Date& d2);
bool operator!= (const Date& d1, const Date& d2);
bool operator< (const Date& d1, const Date& d2);
bool operator<= (const Date& d1, const Date& d2);
bool operator> (const Date& d1, const Date& d2);
bool operator>= (const Date& d1, const Date& d2);
Date operator+ (const Date& d, int n);
Date operator- (const Date& d, int n);
int operator- (const Date& d1, const Date& d2);
Date operator+= (Date& d1, int n);
Date operator-= (Date& d1, int n);
Date operator++ (Date& d1, int);
Date operator-- (Date& d1, int);
Date operator++ (Date& d1);
Date operator-- (Date& d1);

// Month functions
int daysInMonth(Month month, int year);
bool isLeapYear(int year);
std::string monthToString(Month month);

#endif /* calendar_hpp */
