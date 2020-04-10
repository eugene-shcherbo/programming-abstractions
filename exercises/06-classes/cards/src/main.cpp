#include <iostream>
#include "console.h"
#include "card.h"

using namespace std;

int main() {

    for (Suit suit = CLUBS; suit <= SPADES; suit++) {
        for (int rank = ACE; rank <= KING; rank++) {
            cout << " " << Card(rank, suit);
        }
        cout << endl;
    }

    Card jackDiamond("JD");
    Card tenClubs("10C");

    cout << "Jack Diamond - " << jackDiamond << endl
         << "10 Clubs - " << tenClubs << endl;

    return 0;
}
