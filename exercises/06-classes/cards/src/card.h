
#ifndef _card_h
#define _card_h

#include <sstream>
#include <string>

extern const int ACE;
extern const int JACK;
extern const int QUEEN;
extern const int KING;

enum Suit { CLUBS, DIAMONDS, HEARTS, SPADES };

class Card {
public:
    Card(std::string cardStr);
    Card(int rank, Suit suit);

    std::string toString() const;
    int getRank() const;
    Suit getSuit() const;

private:
    int _rank;
    Suit _suit;

    bool parseCardString(std::string str);
};

std::ostream& operator<< (std::ostream& os, const Card& c);

Suit suitFromString(const std::string& str);
std::string suitToString(Suit s);
Suit operator++ (Suit& s, int);

#endif
