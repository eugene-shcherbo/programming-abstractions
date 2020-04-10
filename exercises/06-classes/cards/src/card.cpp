#include <sstream>
#include <cctype>
#include "card.h"
#include "strlib.h"

extern const int ACE = 1;
extern const int JACK = 11;
extern const int QUEEN = 12;
extern const int KING = 13;

int parseRank(std::string str);
Suit parseSuit(std::string str);
void validateRank(int rank);
std::string rankToString(int rank);

Card::Card(std::string cardStr) {
    if (!parseCardString(cardStr)) {
        throw "invalid string format";
    }
}

Card::Card(int rank, Suit suit) {
    validateRank(rank);
    _rank = rank;
    _suit = suit;
}

int Card::getRank() const {
    return _rank;
}

Suit Card::getSuit() const {
    return _suit;
}

bool Card::parseCardString(std::string str) {
    size_t cardLength = str.length();

    if (cardLength > 3 || cardLength < 2) {
        return false;
    }

    int rank = parseRank(str.substr(0, cardLength - 1));
    Suit suit = parseSuit(str.substr(cardLength - 1, 1));

    _rank = rank;
    _suit = suit;

    return true;
}

int parseRank(std::string str) {
    if (isnumber(str[0])) {
        int rank = stringToInteger(str);
        validateRank(rank);

        return rank;
    }

    switch (str[0]) {
        case 'A':
            return ACE;
        case 'J':
            return JACK;
        case 'Q':
            return QUEEN;
        case 'K':
            return KING;
        default:
            throw "invalid rank format";
    }


}

void validateRank(int rank) {
    if (rank < ACE || rank > KING) {
        throw "rank can't be less than 1 or more than 13";
    }
}

Suit parseSuit(std::string str) {
    return suitFromString(str);
}

std::string Card::toString() const {
    std::string rankStr = rankToString(_rank);
    std::string suitStr = suitToString(_suit);

    return rankStr + suitStr;
}

std::ostream& operator<< (std::ostream& os, const Card& c) {
    return os << c.toString();
}

std::string rankToString(int rank) {
    switch (rank) {
        case ACE:
            return "A";
        case JACK:
            return "J";
        case QUEEN:
            return "Q";
        case KING:
            return "K";
    }

    return integerToString(rank);
}

Suit suitFromString(const std::string& str) {
    if (str.length() == 0) {
        throw "can't parse Suit from empty string";
    }

    switch (str[0]) {
        case 'C':
            return CLUBS;
        case 'D':
            return DIAMONDS;
        case 'H':
            return HEARTS;
        case 'S':
            return SPADES;
        default:
            throw "invalid string format";
    }
}

std::string suitToString(Suit s) {
    switch (s) {
        case CLUBS:
            return "C";
        case DIAMONDS:
            return "D";
        case HEARTS:
            return "H";
        case SPADES:
            return "S";
        default:
            return integerToString(s);
    }
}

Suit operator++ (Suit& s, int) {
    Suit old = s;
    s = Suit(s + 1);
    return old;
}
