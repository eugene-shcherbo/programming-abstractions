//
//  calendar.cpp
//  calendar
//
//  Created by Eugene Shcherbo on 9/22/19.
//  Copyright © 2019 Eugene Shcherbo. All rights reserved.
//

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
            return "JANUARY";
        case FEBRUARY:
            return "FEBRUARY";
        case MARCH:
            return "MARCH";
        case APRIL:
            return "APRIL";
        case MAY:
            return "MAY";
        case JUNE:
            return "JUNE";
        case JULY:
            return "JULY";
        case AUGUST:
            return "AUGUST";
        case SEPTEMBER:
            return "SEPTEMBER";
        case OCTOBER:
            return "OCTOBER";
        case NOVEMBER:
            return "NOVEMBER";
        case DECEMBER:
            return "DECEMBER";
        default:
            return "???";
    }
}
