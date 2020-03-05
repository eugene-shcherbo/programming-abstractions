#include "Card.h"
#include <sstream>

Card::Card()
    : rank(0), suit(Suit::CLUBS) {
}

Suit parseSuit(std::istringstream& ss) {
    char suit;
    ss >> suit;

    switch (suit) {
        case 'S':
            return Suit::SPADES;
        case 'H':
            return Suit::HEARTS;
        case 'C':
            return Suit::CLUBS;
        case 'D':
            return Suit::DIAMONDS;
        default:
            return Suit::CLUBS;
    }
}

char suitToChar(Suit suit) {
    switch (suit) {
        case Suit::CLUBS:
            return 'C';
        case Suit::HEARTS:
            return 'H';
        case Suit::SPADES:
            return 'S';
        case Suit::DIAMONDS:
            return 'D';
        default:
            return 'C';
    }
}

Card::Card(const std::string& cardName) {
    std::istringstream ss {cardName};
    ss >> rank;
    suit = parseSuit(ss);
}

Card::Card(int r, Suit s)
    : rank(r), suit(s) {
}

std::string Card::toString() {
    std::ostringstream os;
    os << rank;
    os << suitToChar(suit);
    return os.str();
}

int Card::getRank() {
    return rank;
}

Suit Card::getSuit() {
    return suit;
}
