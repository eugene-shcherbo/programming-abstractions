//
//  main.cpp
//  pig-lating
//
//  Created by Eugene Shcherbo on 9/28/19.
//  Copyright © 2019 Eugene Shcherbo. All rights reserved.
//

#include <iostream>
#include <string>
#include <cctype>
#include "mystring.h"
using namespace std;

/* Function prototypes */

MyString lineToPigLatin(MyString line);
MyString wordToPigLatin(MyString word);
int findFirstVowel(MyString word);
bool isVowel(char ch);

int main(int argc, const char * argv[]) {
    cout << "This program translates English to Pig Latin." << endl;
    string line;
    cout << "Enter English text: ";
    getline(cin, line);
    MyString translation = lineToPigLatin(line);
    cout << "Pig Latin output: " << translation << endl;
    return 0;
}

MyString lineToPigLatin(MyString line) {
    MyString result("");
    int start = -1;
    
    for (int i = 0; i < line.length(); ++i) {
        char ch = line[i];
        if (isalpha(ch)) {
            if (start == -1) start = i;
        } else {
            if (start >= 0) {
                result += wordToPigLatin(line.substr(start, i - start));
                start = -1;
            }
            result += MyString(string(1, ch));
        }
    }
    
    if (start >= 0) result += wordToPigLatin(line.substr(start));
    
    return result;
}

MyString wordToPigLatin(MyString word) {
    int vp = findFirstVowel(word);
    if (vp == -1) {
        return word;
    } else if (vp == 0) {
        return word + MyString("way");
    } else {
        MyString head = word.substr(0, vp);
        MyString tail = word.substr(vp);
        return tail + head + MyString("ay");
    }
}

int findFirstVowel(MyString word) {
    for (int i = 0; i < word.length(); ++i) {
        if (isVowel(word[i])) return i;
    }
    return -1;
}

bool isVowel(char ch) {
    switch (ch) {
        case 'A': case 'E': case 'I': case 'O': case 'U':
        case 'a': case 'e': case 'i': case 'o': case 'u':
            return true;
        default:
            return false;
    }
}
