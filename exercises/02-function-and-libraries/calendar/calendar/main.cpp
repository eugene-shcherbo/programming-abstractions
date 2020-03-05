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

int main(int argc, const char * argv[]) {
    int year;
    cout << "Enter a year: ";
    cin >> year;
    
    for (int i = JANUARY; i <= DECEMBER; ++i) {
        Month month = static_cast<Month>(i);
        cout << monthToString(month) << " has "
            << daysInMonth(month, year) << " days." << endl;
    }
    
    return 0;
}
