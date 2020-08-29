#include <iostream>
#include "simpio.h"
#include "nimgame.h"

NimMove createMove(int taken) {
    return NimMove{taken};
}

NimGame::NimGame(int coinsNum, Player startingPlayer) {
    coins_ = coinsNum;
    whoseTurn_ = startingPlayer;
}

void NimGame::initGame()
{}

bool NimGame::isGameOver() const {
    return coins_ <= 1;
}

void NimGame::displayGame() const {
    std::cout << "There are " << coins_ << " coins in the pile." << std::endl;
}

NimMove NimGame::getUserMove() const {
    while (true) {
        int taken = getInteger("How many would you like? ");
        int limit = coins_ < MAX_MOVE ? coins_ : MAX_MOVE;

        if (taken < 0 || taken > limit) {
            std::cout << "That's cheating! Please choose a number";
            std::cout << "between 1 and " << limit << "." << std::endl;
            displayGame();
        }

        return createMove(taken);
    }
}

void NimGame::announceResult() const {
    if (coins_ == 0) {
        std::cout << "You took the last coin. You lose." << std::endl;
    } else {
        std::cout << "There is only one coin left." << std::endl;

        if (whoseTurn_ == HUMAN) {
            std::cout << "I win." << std::endl;
        } else {
            std::cout << "I lose." << std::endl;
        }
    }
}

void NimGame::makeMove(NimMove move) {
    coins_ -= move.taken;
    switchTurn();
}

void NimGame::displayMove(NimMove move) {
    std::cout << "I'll take " << move.taken << "." << std::endl;
}

void NimGame::retractMove(NimMove move) {
    coins_ += move.taken;
    switchTurn();
}

int NimGame::evaluateStaticPosition() const {
    return coins_ % (MAX_MOVE + 1) == 1 ? LOSING_POSITION : WINNING_POSITION;
}

void NimGame::generateMoves(Vector<NimMove>& moves) const {
    int limit = coins_ < MAX_MOVE ? coins_ : MAX_MOVE;

    for (int i = 1; i <= limit; i++) moves.add(createMove(i));
}

int NimGame::maxDepth() const {
    return MAX_DEPTH;
}

int NimGame::winningRating() const {
    return WINNING_POSITION;
}

void NimGame::switchTurn() {
    whoseTurn_ = whoseTurn_ == HUMAN ? COMPUTER : HUMAN;
}

Player NimGame::getCurrentPlayer() const {
    return whoseTurn_;
}
