#include <iostream>
#include <iomanip>
#include "vector.h"
#include "simpio.h"
#include "tictactoegame.h"

constexpr char TicTacToeGame::EMPTY;

bool equals(char one, char two, char three, char mark) {
    return one == two && two == three && three == mark;
}

int getSquareIndex(int r, int c) {
    if ((r < 0 && c < 0) || (r >= 3 && c >= 3)) error("Row and column passed are outsite of the bord");
    return r * 3 + c;
}

char getSquareValue(const Vector<char>& board, int r, int c) {
    return board[getSquareIndex(r, c)];
}

void printBoard(const Vector<char>& board) {
    std::cout << std::endl;
    for (int r = 0; r < 3; r++) {
        if (r != 0) std::cout << "---+---+---" << std::endl;
        for (int c = 0; c < 3; c++) {
            if (c != 0) std::cout << '|';
            std::cout << ' ' << getSquareValue(board, r, c) << ' ';
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

Player opponent(Player player) {
    return player == HUMAN ? COMPUTER : HUMAN;
}

char promptUserForSymbol() {
    while (true) {
        char symbol = getChar("Would you like to be X or O? ");
        if (symbol == 'X' || symbol == 'O') return symbol;
        std::cout << "Wrong symbol. Please try again" << std::endl;
    }
}

void TicTacToeGame::initGame() {
    std::cout << "Welcome to TicTacToe, the game of three in a row." << std::endl;

    humanSymbol_ = promptUserForSymbol();
    computerSymbol_ = humanSymbol_ == 'X' ? 'O' : 'X';
    whoseTurn_ = humanSymbol_ == 'X' ? HUMAN : COMPUTER;

    std::cout << "I'll be " << computerSymbol_ << " and you'll be " << humanSymbol_ << "." << std::endl;
    std::cout << "The squares are numbered like this:" << std::endl;

    Vector<char> demoBoard {
        '1', '2', '3',
        '4', '5', '6',
        '7', '8', '9'
    };

    printBoard(demoBoard);
}

bool TicTacToeGame::isGameOver() const {
    return isBoardFull() || hasWon(HUMAN) || hasWon(COMPUTER);
}

bool TicTacToeGame::isBoardFull() const {
    return turnsTaken_ == 9;
}

bool TicTacToeGame::isBoardEmpty() const {
    return turnsTaken_ == 0;
}

void TicTacToeGame::displayGame() const {
    if (!isBoardEmpty()) {
        std::cout << "The game now looks like this:" << std::endl;
        printBoard(board_);
    }
}

void TicTacToeGame::announceResult() const {
    std::cout << "The final position looks like this:" << std::endl;
    printBoard(board_);

    // checkWinner -> Player* (HUMAN, PLAYER, nullptr)

    if (hasWon(HUMAN)) {
        std::cout << "You win." << std::endl;
    } else if (hasWon(COMPUTER)) {
        std::cout << "I win." << std::endl;
    } else {
        std::cout << "Tie." << std::endl;
    }

}

TicTacToeMove TicTacToeGame::getUserMove() const {
    std::cout << "Your move." << std::endl;
    int square;

    while (true) {
        square = getInteger("What square? ");
        if (isMoveToSquareLegal(square)) break;
        std::cout << "That move is illegal. Try again." << std::endl;
    }

    return TicTacToeMove { square };
}

void TicTacToeGame::makeMove(TicTacToeMove move) {
    board_[move.square - 1] = playerMark(whoseTurn_);
    switchTurn();
    turnsTaken_++;
}

int TicTacToeGame::evaluateStaticPosition() const {
    if (hasWon(whoseTurn_)) return WINNING_POSITION;
    else if (hasWon(opponent(whoseTurn_))) return LOOSING_POSITION;
    else return NEUTRAL_POSITION;
}

bool TicTacToeGame::hasWon(Player player) const {
    char mark = playerMark(player);

    for (int i = 0; i < 3; i++) {
        if (rowWinner(i, mark)) return true;
        if (columnWinner(i, mark)) return true;
    }
    return diagonalWinner(mark);
}

bool TicTacToeGame::rowWinner(int row, char mark) const {
    return equals(
        getSquareValue(board_, row, 0),
        getSquareValue(board_, row, 1),
        getSquareValue(board_, row, 2),
        mark);
}

bool TicTacToeGame::columnWinner(int col, char mark) const {
    return equals(
        getSquareValue(board_, 0, col),
        getSquareValue(board_, 1, col),
        getSquareValue(board_, 2, col),
        mark);
}

bool TicTacToeGame::diagonalWinner(char mark) const {
    return equals(board_[0], board_[4], board_[8], mark)
        || equals(board_[2], board_[4], board_[6], mark);
}

void TicTacToeGame::displayMove(TicTacToeMove move) {
    std::cout << "I'll move to " << move.square << "." << std::endl;
}

void TicTacToeGame::retractMove(TicTacToeMove move) {
    board_[move.square - 1] = EMPTY;
    switchTurn();
    turnsTaken_--;
}

void TicTacToeGame::generateMoves(Vector<TicTacToeMove>& moves) const {
    for (int s = 0; s < board_.size(); s++) {
        if (isMoveToSquareLegal(s + 1)) {
            moves.add(TicTacToeMove { s + 1 });
        }
    }
}

int TicTacToeGame::maxDepth() const {
    return MAX_DEPTH;
}

int TicTacToeGame::winningRating() const {
    return WINNING_POSITION;
}

Player TicTacToeGame::getCurrentPlayer() const {
    return whoseTurn_;
}

void TicTacToeGame::switchTurn() {
    whoseTurn_ = whoseTurn_ == HUMAN ? COMPUTER : HUMAN;
}

bool TicTacToeGame::isMoveToSquareLegal(int square) const {
    if (square < 1 || square > 9) return false;
    return board_[square - 1] == EMPTY;
}

char TicTacToeGame::playerMark(Player player) const {
    return player == HUMAN ? humanSymbol_ : computerSymbol_;
}
