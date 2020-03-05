#include <iostream>

#include "gwindow.h"
#include "console.h"
#include "simpio.h"

using namespace std;

const int N_COINS = 13;
const int MAX_MOVE = 3;
const int NO_GOOD_MOVE = -1;

enum Player { HUMAN, COMPUTER };

Player opponent(Player player) {
    return player == HUMAN ? COMPUTER : HUMAN;
}

const Player STARTING_PLAYER = COMPUTER;

class SimpleNim {
public:
    void play();
    void printInstructions();

private:
    int getComputerMove();
    int findGoodMove(int nCoins);
    bool isBadPosition(int nCoins);
    int getUserMove();
    void announceResult();

    int nCoins;
    Player whoseTurn;
};

int main() {
    SimpleNim game;
    game.printInstructions();
    game.play();

    return 0;
}

void SimpleNim::play() {
        nCoins = N_COINS;
        whoseTurn = STARTING_PLAYER;

        while (nCoins > 1) {
            cout << "There are " << nCoins << " coins in the pile." << endl;

            if (whoseTurn == HUMAN) {
                nCoins -= getUserMove();
            } else {
                int nTaken = getComputerMove();
                cout << "I'll take " << nTaken << "." << endl;
                nCoins -= nTaken;
            }
            whoseTurn = opponent(whoseTurn);
        }
        announceResult();
    }

void SimpleNim::printInstructions() {
        cout << "Welcome to the game of Nim!" << endl;
        cout << "In this game, we will start with a pile of" << endl;
        cout << N_COINS << " coins on the table. On each turn, you" << endl;
        cout << "and I will alternatively take between 1 and" << endl;
        cout << MAX_MOVE << " coins from the table. The player who" << endl;
        cout << "takes the last coin loses." << endl << endl;
    }

int SimpleNim::getComputerMove() {
        int nTaken = findGoodMove(nCoins);
        return nTaken == NO_GOOD_MOVE ? 1 : nTaken;
    }

int SimpleNim::findGoodMove(int nCoins) {
    int limit = (nCoins < MAX_MOVE) ? nCoins : MAX_MOVE;

    for (int nTaken = 1; nTaken <= limit; nTaken++) {
        if (isBadPosition(nCoins - nTaken)) return nTaken;
        }

        return NO_GOOD_MOVE;
    }

bool SimpleNim::isBadPosition(int nCoins) {
        if (nCoins == 1) return true;
        return findGoodMove(nCoins) == NO_GOOD_MOVE;
    }

int SimpleNim::getUserMove() {
        while (true) {
            int nTaken = getInteger("How many would you like? ");
            int limit = nCoins < MAX_MOVE ? nCoins : MAX_MOVE;
            if (nTaken > 0 && nTaken <= limit) return nTaken;
            cout << "That's cheating! Please choose a number";
            cout << "between 1 and " << limit << "." << endl;
            cout << "There are " << nCoins << " coins in the pile." << endl;
        }
    }

void SimpleNim::announceResult() {
        if (nCoins == 0) {
            cout << "You took the last coin. You lose." << endl;
        } else {
            cout << "There is only one coin left." << endl;

            if (whoseTurn == HUMAN) {
                cout << "I win." << endl;
            } else {
                cout << "I lose." << endl;
            }
        }
    }
