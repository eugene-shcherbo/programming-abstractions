#ifndef CARD_H
#define CARD_H

#include <string>

enum Rank { ACE = 1, JACK = 11, QUEEN = 12, KING = 13 };

enum Suit { CLUBS, DIAMONDS, HEARTS, SPADES };

class Card {

private:
    int rank;
    Suit suit;

public:
    Card();
    Card(const std::string& cardName);
    Card(int rank, Suit suit);
    std::string toString();
    int getRank();
    Suit getSuit();
};

#endif // CARD_H
