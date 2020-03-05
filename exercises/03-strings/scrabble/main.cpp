#include <iostream>
#include <string>
using namespace std;

int countScrabbleScore(const string& word);
short score(char ch);
void testScrabble(const string& word, int expected);

int main()
{
    testScrabble("FARM", 9);
    testScrabble("MOTHER", 11);
    testScrabble("faRM", 4);

    return 0;
}

void testScrabble(const string& word, int expected) {
    cout << word << " - expected = " << expected << "; actual = "
         << countScrabbleScore(word) << endl;
}

int countScrabbleScore(const string& word) {
    int sum = 0;
    for (int i = 0; i < word.length(); ++i) {
        sum += score(word[i]);
    }
    return sum;
}

short score(char ch) {
    switch(ch) {
        case 'A': case 'E': case 'I': case 'L': case 'N':
        case 'O': case 'R': case 'S': case 'T': case 'U':
            return 1;
        case 'D': case 'G':
            return 2;
        case 'B': case 'C': case 'M': case 'P':
            return 3;
        case 'F': case 'H': case 'V': case 'W': case 'Y':
            return 4;
        case 'K':
            return 5;
        case 'J': case 'X':
            return 8;
        case 'Q': case 'Z':
            return 10;
        default:
            return 0;
    }
}
