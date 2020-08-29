#ifndef TICTACTOEGAME_H
#define TICTACTOEGAME_H

#include <string>
#include "vector.h"
#include "twoplayergame.h"

struct TicTacToeMove {
    int square;
};

class TicTacToeGame : public TwoPlayerGame<TicTacToeMove> {

protected:
    void initGame() override;
    bool isGameOver() const override;
    void displayGame() const override;
    void announceResult() const override;
    TicTacToeMove getUserMove() const override;
    void makeMove(TicTacToeMove move) override;
    int evaluateStaticPosition() const override;
    void displayMove(TicTacToeMove move) override;
    void retractMove(TicTacToeMove move) override;
    void generateMoves(Vector<TicTacToeMove> &moves) const override;
    int maxDepth() const override;
    int winningRating() const override;
    Player getCurrentPlayer() const override;
    void switchTurn();

private:
    bool columnWinner(int col, char mark) const;
    bool rowWinner(int row, char mark) const;
    bool diagonalWinner(char mark) const;
    bool isMoveToSquareLegal(int square) const;
    bool hasWon(Player player) const;
    char playerMark(Player player) const;
    bool isBoardFull() const;
    bool isBoardEmpty() const;

    static constexpr char EMPTY = ' ';
    static constexpr int MAX_DEPTH = 10;
    static constexpr int WINNING_POSITION = 1000;
    static constexpr int LOOSING_POSITION = -WINNING_POSITION;
    static constexpr int NEUTRAL_POSITION = WINNING_POSITION / 2;

    Player whoseTurn_;
    char humanSymbol_;
    char computerSymbol_;
    int turnsTaken_ = 0;

    Vector<char> board_ {
        ' ', ' ', ' ',
        ' ', ' ', ' ',
        ' ', ' ', ' '
    };
};

#endif // TICTACTOEGAME_H
