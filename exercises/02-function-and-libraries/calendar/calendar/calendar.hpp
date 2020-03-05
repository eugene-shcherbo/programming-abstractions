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

int daysInMonth(Month month, int year);

bool isLeapYear(int year);

std::string monthToString(Month month);

#endif /* calendar_hpp */
