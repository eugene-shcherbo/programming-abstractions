#include <iostream>
#include "console.h"
#include "vector.h"
#include "set.h"
#include "Card.h"

using namespace std;

int countFifteens(Vector<Card>& cards);
int countSubsetSumWays(const Vector<Card>& cards, int target) ;

int main() {
    Vector<Card> cards {
        Card(Rank::ACE, Suit::DIAMONDS),
        Card(5, Suit::CLUBS),
        Card(10, Suit::SPADES),
        Card(4, Suit::HEARTS),
        Card(9, Suit::CLUBS)
    };

    Vector<Card> cards2 {
        Card(5, Suit::CLUBS),
        Card(5, Suit::DIAMONDS),
        Card(5, Suit::HEARTS),
        Card(5, Suit::DIAMONDS),
        Card(Rank::JACK, Suit::CLUBS)
    };

    cout << countFifteens(cards) << endl;
    cout << countFifteens(cards2) << endl;


    return 0;
}

int countFifteens(Vector<Card>& cards) {
    return countSubsetSumWays(cards, 15);
}

int countSubsetSumWays(const Vector<Card>& cards, int target) {
    if (cards.isEmpty()) {
        return target == 0 ? 1 : 0;
    } else {
        Vector<Card> rest = cards;
        Card el = rest.removeBack();

        int rank = el.getRank() > 10 ? 10 : el.getRank();

        return countSubsetSumWays(rest, target) + countSubsetSumWays(rest, target - rank);
    }
}
