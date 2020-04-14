//
//  calendar.cpp
//  calendar
//
//  Created by Eugene Shcherbo on 9/22/19.
//  Copyright © 2019 Eugene Shcherbo. All rights reserved.
//

#include <sstream>
#include <iomanip>
#include "calendar.hpp"

int daysInMonth(Month month, int year) {
    switch (month) {
        case APRIL:
        case JUNE:
        case SEPTEMBER:
        case NOVEMBER:
            return 30;
        case FEBRUARY:
            return isLeapYear(year) ? 29 : 28;
        default:
            return 31;
    }
}

bool isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0)
        || year % 400 == 0;
}

std::string monthToString(Month month) {
    switch (month) {
        case JANUARY:
            return "January";
        case FEBRUARY:
            return "February";
        case MARCH:
            return "March";
        case APRIL:
            return "April";
        case MAY:
            return "May";
        case JUNE:
            return "June";
        case JULY:
            return "July";
        case AUGUST:
            return "August";
        case SEPTEMBER:
            return "September";
        case OCTOBER:
            return "October";
        case NOVEMBER:
            return "November";
        case DECEMBER:
            return "December";
        default:
            return "???";
    }
}

Date::Date() {
    month = JANUARY;
    day = 1;
    year = 1900;
}

Date::Date(Month m, int d, int y) {
    if (y <= 0) {
        throw "year can't be negative.";
    } else if (d < 1 || d > daysInMonth(m, y)) {
        throw "day can't be beyond the month days.";
    } else {
        month = m;
        day = d;
        year = y;
    }
}

Date::Date(int d, Month m, int y) : Date(m, d, y) {
}

int Date::getDay() const {
    return day;
}

Month Date::getMonth() const {
    return month;
}

int Date::getYear() const {
    return year;
}

std::string Date::toString() const {
    std::ostringstream os;
    os << std::setfill('0') << std::setw(2) << day << '-'
    << std::setw(3) << monthToString(month).substr(0, 3) << '-'
        << std::setw(4) << year;
    return os.str();
}

std::ostream& operator<< (std::ostream& os, const Date& d) {
    return os << d.toString();
}

bool operator== (const Date& d1, const Date& d2) {
    return d1.getDay() == d2.getDay()
        && d1.getMonth() == d2.getMonth()
        && d1.getYear() == d2.getYear();
}

bool operator> (const Date& d1, const Date& d2) {
    return (d1.getYear() > d2.getYear())
        || (d1.getYear() == d2.getYear() && d1.getMonth() > d2.getMonth())
        || (d1.getMonth() == d2.getMonth() && d1.getDay() > d2.getDay());
}

bool operator>= (const Date& d1, const Date& d2) {
    return d1 == d2 || d1 > d2;
}

bool operator!= (const Date& d1, const Date& d2) {
    return !(d1 == d2);
}

bool operator< (const Date& d1, const Date& d2) {
    return !(d1 >= d2);
}

bool operator<= (const Date& d1, const Date& d2) {
    return d1 == d2 || d1 < d2;
}

Date operator+ (const Date& d, int n) {
    if (n < 0) {
        return d - abs(n);
    }
    
    int newDay = d.getDay();
    Month newMonth = d.getMonth();
    int newYear = d.getYear();
    
    while (n > 0) {
        newDay++;
        
        if (newDay > daysInMonth(newMonth, newYear)) {
            newDay = 1;
            newMonth = Month(newMonth + 1);
            
            if (newMonth > DECEMBER) {
                newMonth = JANUARY;
                newYear++;
            }
        }
        n--;
    }
    
    return Date(newDay, newMonth, newYear);
}

Date operator- (const Date& d, int n) {
    if (n < 0) {
        return d + abs(n);
    }
    
    int newDay = d.getDay();
    Month newMonth = d.getMonth();
    int newYear = d.getYear();
    
    while (n > 0) {
        newDay--;
        
        if (newDay < 1) {
            newMonth = Month(newMonth - 1);
            
            if (newMonth < JANUARY) {
                newMonth = DECEMBER;
                newYear--;
            }
            
            newDay = daysInMonth(newMonth, newYear);
        }
        n--;
    }
    
    return Date(newDay, newMonth, newYear);
}

int operator- (const Date& d1, const Date& d2) {
    Date curr = d2;
    int days = 0;
    
    while (curr < d1) {
        curr = curr + 1;
        days++;
    }
    
    return days;
}

Date operator+= (Date& d, int n) {
    Date newDate = d + n;
    d = newDate;
    return d;
}

Date operator-= (Date& d, int n) {
    return d += (-n);
}

Date operator++ (Date& d, int) {
    Date old = d;
    d += 1;
    return old;
}

Date operator-- (Date& d, int) {
    Date old = d;
    d -= 1;
    return old;
}

Date operator++ (Date& d) {
    return d += 1;
}

Date operator-- (Date& d) {
    return d -= 1;
}
