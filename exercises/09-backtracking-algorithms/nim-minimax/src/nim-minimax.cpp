#include <iostream>

#include "gwindow.h"
#include "console.h"
#include "simpio.h"

using namespace std;

const int N_COINS = 13;
const int MAX_MOVE = 3;
const int MAX_DEPTH = 3;
const int WINNING_POSITION = 1000;
const int LOSING_POSITION = -WINNING_POSITION;

enum Player { HUMAN, COMPUTER };

Player opponent(Player player) {
    return player == HUMAN ? COMPUTER : HUMAN;
}

const Player STARTING_PLAYER = COMPUTER;

struct Move {
    int nTaken;
};

class SimpleNim {
public:
    void play();
    void printInstructions();

private:
    int getComputerMove();
    int getUserMove();
    void announceResult();

    int nCoins;
    Player whoseTurn;

    Move findBestMove();
    Move findBestMove(int depth, int& rating);
    int evaluatePosition(int depth);
    void generateMoveList(Vector<Move>& list);
    void makeMove(Move move);
    void retractMove(Move move);
    bool isGameOver();
    int evaluateStaticPosition();
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
    Move bestMove = findBestMove();
    return bestMove.nTaken;
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

Move SimpleNim::findBestMove() {
    int rating;
    return findBestMove(0, rating);
}

Move SimpleNim::findBestMove(int depth, int& rating) {
    Vector<Move> moveList;
    Move bestMove;
    int minRating = WINNING_POSITION + 1;
    generateMoveList(moveList);

    if (moveList.isEmpty()) error("No moves available");

    for (Move move: moveList) {
        makeMove(move);
        int moveRating = evaluatePosition(depth + 1);
        if (moveRating < minRating) {
            bestMove = move;
            minRating = moveRating;
        }
        retractMove(move);
    }
    rating = -minRating;

    return bestMove;
}

void SimpleNim::generateMoveList(Vector<Move>& list) {
    int limit = nCoins < MAX_MOVE ? nCoins : MAX_MOVE;

    for (int i = 1; i <= limit; i++)
        list.add(Move{i});
}

void SimpleNim::makeMove(Move move) {
    nCoins -= move.nTaken;
}

void SimpleNim::retractMove(Move move) {
    nCoins += move.nTaken;
}

int SimpleNim::evaluatePosition(int depth) {
    if (isGameOver() || depth >= MAX_DEPTH) {
        return evaluateStaticPosition();
    }
    int rating;
    findBestMove(depth, rating);
    return rating;
}

bool SimpleNim::isGameOver() {
    return nCoins <= 1;
}

/*
 * nCoins % (MAX_MOVE + 1) == 1 means that you are in the position
 * when you either have 1 coins (cause 1 always less than MAX_MOVE + 1)
 * or you can get 1 coin (to make your opponent lose) by taking MAX_MOVE + 1 coins
 * because 1 = nCoins - n * (MAX_MOVE + 1) which is impossible by definition.
 */

int SimpleNim::evaluateStaticPosition() {
    return nCoins % (MAX_MOVE + 1) == 1  ? LOSING_POSITION : WINNING_POSITION;
}
