#include <iostream>
#include "console.h"

using namespace std;

void listPermutations(string str);
void permutationsHelper(string str, int index);
bool shouldSwap(const string& str, int start, int end);
void swap(string& str, int a, int b);

int main() {
    listPermutations("ACBC");

    return 0;
}

void listPermutations(string str) {
    permutationsHelper(str, 0);
}

void permutationsHelper(string str, int index) {
    if (index == str.length() - 1) {
        cout << str << endl;
    } else {
        char ch = str[index];

        for (int i = index; i < str.length(); ++i) {
            if (shouldSwap(str, index, i)) {
                swap(str, index, i);
                permutationsHelper(str, index + 1);
                swap(str, i, index);
            }

        }
    }

}

bool shouldSwap(const string& str, int start, int end) {
    for (int i = start; i < end && i < str.length(); ++i) {
        if (str[i] == str[end]) {
            return false;
        }
    }
    return true;
}

void swap(string& str, int a, int b) {
    int tmp = str[a];
    str[a] = str[b];
    str[b] = tmp;
}

void sortCharacters(string& str) {
    for (size_t lh = 0; lh < str.size(); lh++) {
        size_t smallest = lh;
        for (size_t rh = lh + 1; rh < str.size(); rh++) {
            if (str[rh] < str[smallest])
                smallest = rh;
        }
        swap(str[lh], str[smallest]); // swap is in <algorithm>
    }
}
