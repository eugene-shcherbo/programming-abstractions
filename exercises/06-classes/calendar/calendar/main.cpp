//
//  main.cpp
//  calendar
//
//  Created by Eugene Shcherbo on 9/22/19.
//  Copyright © 2019 Eugene Shcherbo. All rights reserved.
//

#include <iostream>
#include "calendar.hpp"
using namespace std;

string boolToString(bool val) {
    return val ? "true" : "false";
}

void monthTest() {
    int year;
    cout << "Enter a year: ";
    cin >> year;
    
    for (int i = JANUARY; i <= DECEMBER; ++i) {
        Month month = static_cast<Month>(i);
        cout << monthToString(month) << " has "
            << daysInMonth(month, year) << " days." << endl;
    }
}

void dateTest() {
    Date d1;
    Date d2(JULY, 20, 1969);
    Date d3(20, DECEMBER, 2000);
    
    cout << "d1 = " << d1 << endl;
    cout << "d2 = " << d2 << endl;
    cout << "d3 = " << d3 << endl;
}

void operatorsTest() {
    Date d1(JULY, 20, 1969);
    Date d2(20, JULY, 1969);
    Date d3(1, JANUARY, 1970);
    
    cout << "----Relationship operators----" << endl;
    cout << d1 << " == " << d2 << " " << boolToString(d1 == d2) << endl;
    cout << d1 << " != " << d2 << " " << boolToString(d1 != d2) << endl;
    cout << d1 << " == " << d3 << " " << boolToString(d1 == d3) << endl;
    cout << d1 << " != " << d3 << " " << boolToString(d1 != d3) << endl;
    cout << d1 << " < " << d2 << " " << boolToString(d1 < d2) << endl;
    cout << d1 << " <= " << d2 << " " << boolToString(d1 <= d2) << endl;
    cout << d3 << " > " << d2 << " " << boolToString(d3 > d2) << endl;
    cout << d3 << " >= " << d2 << " " << boolToString(d3 >= d2) << endl;
    cout << d2 << " > " << d3 << " " << boolToString(d2 > d3) << endl;
    
    cout << endl << "----Ariphmetic operators-----" << endl;
    
    Date electionDay(6, NOVEMBER, 2012);
    Date inaugurationDay(21, JANUARY, 2013);
    int diff = 76;
    
    cout << electionDay + diff << " == " << inaugurationDay << " "
        << boolToString(electionDay + diff == inaugurationDay)
        << endl;
    
    cout << inaugurationDay - diff << " == " << electionDay << " "
        << boolToString(inaugurationDay - diff == electionDay)
        << endl;
    
    cout << electionDay - (-diff) << " == " << inaugurationDay << " "
        << boolToString(electionDay - (-diff) == inaugurationDay)
        << endl;
    
    cout << inaugurationDay + (-diff) << " == " << electionDay << " "
        << boolToString(inaugurationDay + (-diff) == electionDay)
        << endl;
    
    cout << inaugurationDay - electionDay << " == " << diff << " "
        << boolToString(inaugurationDay - electionDay == diff)
        << endl;
    
    int days = 0;
    for (Date d = electionDay; d <= inaugurationDay; d++) {
        days++;
    }
    
    cout << "Number of days == " << days - 1 << endl;
    
    days = 0;
    for (Date d = inaugurationDay; d >= electionDay; d--) {
        days++;
    }
    
    cout << "Number of days == " << days - 1 << endl;
}

int main(int argc, const char * argv[]) {
    // monthTest();
    // dateTest();
    operatorsTest();
    
    return 0;
}
