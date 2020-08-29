#ifndef NIMGAME_H
#define NIMGAME_H

#include "twoplayergame.h"

struct NimMove {
    int taken;
};

class NimGame : public TwoPlayerGame<NimMove> {

public:
    NimGame(int coinsNumber, Player startingPlayer);

protected:
    void initGame() override;
    bool isGameOver() const override;
    void displayGame() const override;
    NimMove getUserMove() const override;
    void announceResult() const override;
    void makeMove(NimMove move) override;
    void displayMove(NimMove move) override;
    void retractMove(NimMove move) override;
    int evaluateStaticPosition() const override;
    void generateMoves(Vector<NimMove> &moves) const override;
    int maxDepth() const override;
    int winningRating() const override;
    void switchTurn();
    Player getCurrentPlayer() const override;

private:
    int coins_;
    Player whoseTurn_;

    static constexpr int WINNING_POSITION = 1000;
    static constexpr int LOSING_POSITION = -WINNING_POSITION;
    static constexpr int MAX_MOVE = 3;
    static constexpr int MAX_DEPTH = 10;
};

#endif // NIMGAME_H
