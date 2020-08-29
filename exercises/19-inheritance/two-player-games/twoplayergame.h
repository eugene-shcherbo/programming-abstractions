#ifndef TWOPLAYERGAME_H
#define TWOPLAYERGAME_H

#include "error.h"
#include "vector.h"
#include "twoplayergamebase.h"

enum Player { HUMAN, COMPUTER };

template <class MoveType>
class TwoPlayerGame : public TwoPlayerGameBase {

public:
    void play() final override;

protected:
    virtual void initGame() = 0;
    virtual bool isGameOver() const = 0;
    virtual void displayGame() const = 0;
    virtual void makeMove(MoveType move) = 0;
    virtual void displayMove(MoveType move) = 0;
    virtual void announceResult() const = 0;
    virtual MoveType getUserMove() const = 0;
    virtual void generateMoves(Vector<MoveType>& moves) const = 0;
    virtual void retractMove(MoveType move) = 0;
    virtual int evaluateStaticPosition() const = 0;
    virtual int winningRating() const = 0;
    virtual int maxDepth() const = 0;
    virtual Player getCurrentPlayer() const = 0;
private:
    MoveType getComputerMove();
    MoveType findBestMove();
    MoveType findBestMove(int depth, int& rating);
    int evaluatePosition(int depth);
};

template <class MoveType>
void TwoPlayerGame<MoveType>::play() {
    initGame();
    while (!isGameOver()) {
        displayGame();
        MoveType move;
        if (getCurrentPlayer() == HUMAN) {
            move = getUserMove();
        } else {
            move = getComputerMove();
            displayMove(move);
        }
        makeMove(move);
    }
    announceResult();
}

template <class MoveType>
MoveType TwoPlayerGame<MoveType>::getComputerMove() {
    return findBestMove();
}

template <class MoveType>
MoveType TwoPlayerGame<MoveType>::findBestMove() {
    int rating;
    return findBestMove(0, rating);
}

template <class MoveType>
MoveType TwoPlayerGame<MoveType>::findBestMove(int depth, int& rating) {
    Vector<MoveType> moves;
    MoveType bestMove;

    int minRating = winningRating() + 1;
    generateMoves(moves);

    if (moves.isEmpty()) error("No moves available");

    for (const MoveType& move : moves) {
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

template <class MoveType>
int TwoPlayerGame<MoveType>::evaluatePosition(int depth) {
    if (isGameOver() || depth >= maxDepth()) {
        return evaluateStaticPosition();
    }
    int rating;
    findBestMove(depth, rating);
    return rating;
}

#endif // TWOPLAYERGAME_H
