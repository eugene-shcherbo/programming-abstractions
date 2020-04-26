/* TODO: This is the file you edit! (and the only file you edit)
 */

#include <iostream>
#include "grid.h"
#include "set.h"
#include "vector.h"
#include "simpio.h"
#include "console.h"
#include "random.h"
#include "gevents.h"
#include "filelib.h"

#include "marbletypes.h"
#include "marblegraphics.h"
#include "compression.h"

using namespace std;

/* Performs human's turn. Makes appropriate graphics calls to
 * animate the user's movements on the board. When the human's
 * turn is over (either they win or they give up and ask computer
 * to solve the board), it will return the number of marbles remaining.
 */
int  humanPlay(Grid<MarbleType>& board, int marblesRemaining, MarbleGraphics& mg);

/* Performs computer play which will call the recursive exhaustive
 * search function in order to try to find a valid path. If a
 * valid path is found, it will allow the user to step through
 * the solution.
 */
void computerPlay(const Grid<MarbleType>& board, int marblesRemaining, MarbleGraphics& mg);

/* Initializes the game board by either reading a file or setting
 * up the default board.
 * Parameter validEnds: a set of valid end locations on the board
 * where the last marble must finish in order to have won the game.
 * If the last marble ends in a location not in this set, then the
 * game is lost.
 * Returns the number of marbles on the gameboard.
 */
int  initializeBoard(Grid<MarbleType>& board);

/* Reads in the board from the file and populates the board along with
 * the set of valid end points.
 * Precondition: ifstream file parameter is already open with a correctly
 * formatted file.
 * Returns the number of marbles on the gameboard.
 */
int  readBoardFromFile(Grid<MarbleType>& board, ifstream& file);

/* Populates the given board with the default board configuration
 * and only has the position (3,3) as a valid end point for the game.
 */
void setUpDefaultBoard(Grid<MarbleType>& board);

/* Performs the specified move on the board.
 * Precondition: this move must be valid.
*/
void makeMove(Move move, Grid<MarbleType>& board);

/* Undoes the specified move on the board.
 * Note: it's important to realize that this method is
 * necessary because you have to replace the jumped marble
 * so you can't just call makeMove() with the start and end
 * locations swapped.
 */
void undoMove(Move move, Grid<MarbleType>& board);

/* Checks whether the given move is valid on this board.
 * A move is valid if
 * 1) A marble occupies the start location.
 * 2) The end location is empty.
 * 3) A marble occupies the space in between the start and end locations.
 * 4) The start and end locations are in an orthogonal direction and
 *    exactly 2 spaces away (i.e. no diagonal moves)
 * If all 3 of these properties are true, then this method will
 * return that the move is valid.
 */
bool isValidMove(Move move, const Grid<MarbleType>& board);

/* Board: starting board that you should find a solution for.
 * Marbles Left: number of marbles left in the game.
 * ExploredBoards: a set of encoded boards which you have already checked. You
 *                 should use this to avoid doing duplicate work in your recursion.
 * MoveHistory: the current set of moves from the starting board that the
 *              recursion is considering.
 *
 * Return: Returns true or false of whether it's possible to solve the
 *         starting board.
 */
bool solvePuzzle(const Grid<MarbleType>& board, int marblesLeft,
                 Set<uint32_t>& exploredBoards, Vector<Move>& moveHistory);

/* Solves the board populating moveHistory which tracks all the moves
 * that lead to the solution.
 */
bool solvePuzzleHelper(Grid<MarbleType>& board, int marblesLeft,
                 Set<uint32_t>& exploredBoards, Vector<Move>& moveHistory);

/* Populates the moves vector with all the possible moves on the current
 * board configuration.
 */
void findPossibleMoves(const Grid<MarbleType>& board, Vector<Move>& moves);

/* Tries to add a move to the given moves vector if the move is a valid one
 * to peform. Otherwise, nothing happens and the collection stays untouched.
*/
void addMove(Move m, const Grid<MarbleType>& board, Vector<Move>& moves);

/* Returns true if the board is solved which means that there is only
 * one marble on the board and this marble is in the center of the board.
 */
bool isBoardSolved(const Grid<MarbleType>& boards, int marbledLeft);

static const int PAUSE_DURATION     = 30;
static const int N_MARBLES_START    = 32;

int main() {
    cout << "Welcome to Marble Solitaire!" << endl;
    MarbleGraphics mg;
    Grid<MarbleType> board(7,7);

    do {
        int marblesRemaining = initializeBoard(board);
        mg.drawBoard(board);
        marblesRemaining = humanPlay(board, marblesRemaining, mg);
        //Only activate computer's turn if human hasn't won
        if (marblesRemaining == 1){
            cout << "Congrats! You have won. :-)" << endl;
        }
        else {
            computerPlay(board, marblesRemaining, mg);
        }
    } while (getLine("Game over! Play again? [y/n] ") == "y");

    return 0;
}

bool solvePuzzle(const Grid<MarbleType>& board, int marblesLeft,
                 Set<uint32_t>& exploredBoards, Vector<Move>& moveHistory) {
    Grid<MarbleType> b = board;
    return solvePuzzleHelper(b, marblesLeft, exploredBoards, moveHistory);
}

bool solvePuzzleHelper(Grid<MarbleType>& board, int marblesLeft,
                       Set<uint32_t>& exploredBoards, Vector<Move>& moveHistory) {

    if (exploredBoards.size() % 10000 == 0) {
        cout << "Boards evaluated: " << exploredBoards.size()
             << "\tDepth: " << moveHistory.size() << endl;
    }

    if (isBoardSolved(board, marblesLeft)) {
        return true;
    } else if (exploredBoards.contains(compressMarbleBoard(board))) {
        return false;
    } else {
        Vector<Move> moves;
        findPossibleMoves(board, moves);
        exploredBoards.add(compressMarbleBoard(board));

        for (Move m: moves) {
            makeMove(m, board);
            moveHistory.add(m);

            if (solvePuzzleHelper(board, marblesLeft - 1, exploredBoards, moveHistory)) {
                return true;
            }

            undoMove(m, board);
            moveHistory.remove(moveHistory.size() - 1);
        }

        return false;
    }
}

bool isBoardSolved(const Grid<MarbleType>& board, int marblesLeft) {
    int r = board.height() / 2;
    int c = board.width() / 2;

    return marblesLeft == 1 && board[r][c] == MARBLE_OCCUPIED;
}

void findPossibleMoves(const Grid<MarbleType>& board, Vector<Move>& moves) {
    for (int r = 0; r < board.height(); r++) {
        for (int c = 0; c < board.width(); c++) {
            addMove(Move(r, c, r - 2, c), board, moves);
            addMove(Move(r, c, r + 2, c), board, moves);
            addMove(Move(r, c, r, c - 2), board, moves);
            addMove(Move(r, c, r, c + 2), board, moves);
        }
    }
}

void addMove(Move m, const Grid<MarbleType>& board, Vector<Move>& moves) {
    if (board.inBounds(m.endRow, m.endCol) && isValidMove(m, board)) {
        int randIndex = randomInteger(0, moves.size() - 1);
        moves.insert(randIndex, m);
    }
}

int humanPlay(Grid<MarbleType>& board, int marblesRemaining, MarbleGraphics& mg) {
    Move move;
    // loop ends when user clicks button asking computer
    // to solve the puzzle or if only one marble left
    while (mg.getNextUserMove(move)){
        if (isValidMove(move, board)) {
            makeMove(move, board);
            mg.makeMove(move);
            marblesRemaining--;
            if(marblesRemaining == 1) break;
        }
        else {
            mg.errorNotification();
        }
    }
    return marblesRemaining;
}

void computerPlay(const Grid<MarbleType>& board, int marblesRemaining, MarbleGraphics& mg){
    Set<uint32_t> exploredBoards;
    Vector<Move> pathToWin;
    cout << "Starting computer solver" << endl;
    bool won = solvePuzzle(board, marblesRemaining, exploredBoards, pathToWin);
    if (!won) {
        cout << "Sorry, no solution found!" << endl;
    }
    else {
        for (Move m : pathToWin){
            cout << "Move " << m;
            mg.makeMove(m);
            getLine("  Press ENTER to continue.");
        }
    }
}

void makeMove(Move move, Grid<MarbleType>& board){
    int jumpedRow = move.startRow + (move.endRow - move.startRow) / 2;
    int jumpedCol = move.startCol + (move.endCol - move.startCol) / 2;
    board[move.startRow][move.startCol] = MARBLE_EMPTY;
    board[move.endRow][move.endCol] = MARBLE_OCCUPIED;
    board[jumpedRow][jumpedCol] = MARBLE_EMPTY;
}

void undoMove(Move move, Grid<MarbleType>& board){
    int jumpedRow = move.startRow + (move.endRow - move.startRow) / 2;
    int jumpedCol = move.startCol + (move.endCol-move.startCol) / 2;
    board[move.startRow][move.startCol] = MARBLE_OCCUPIED;
    board[move.endRow][move.endCol] = MARBLE_EMPTY;
    board[jumpedRow][jumpedCol] = MARBLE_OCCUPIED;
}

bool isValidMove(Move move, const Grid<MarbleType>& board){
    if (board[move.endRow][move.endCol] != MARBLE_EMPTY) return false;
    if (board[move.startRow][move.startCol] != MARBLE_OCCUPIED) return false;
    int rowDelta = abs(move.endRow - move.startRow);
    int colDelta = abs(move.endCol - move.startCol);
    if (!((rowDelta == 2 && colDelta == 0) || (rowDelta == 0 && colDelta == 2))) {
        return false;
    }
    int jumpedRow = move.startRow + (move.endRow - move.startRow) / 2;
    int jumpedCol = move.startCol + (move.endCol - move.startCol) / 2;
    if (board[jumpedRow][jumpedCol] != MARBLE_OCCUPIED) return false;
    return true;
}

int initializeBoard(Grid<MarbleType>& board){
    if(getLine("Do you want to read the board configuration from a file? [y/n] ") == "y"){
        ifstream file;
        promptUserForFile(file, "Enter filename (ie. 'boards/7-Step.txt'): ");
        int marblesRemaining = readBoardFromFile(board, file);
        file.close();
        return marblesRemaining;
    } else { //Do default configuration (Fill in the marbles, leaving four corners blank)
        setUpDefaultBoard(board);
        return N_MARBLES_START;
    }
}

int readBoardFromFile(Grid<MarbleType>& board, ifstream& file){
    //Skip comments at top of file
    string line = "";
    do{
        getline(file, line);
    }
    while(!file.fail() && !line.empty() && line[0] == '#');

    //Read in dimensions
    int row = stringToInteger(line);
    getline(file, line);
    int col = stringToInteger(line);

    //Read board
    int marbleCount = 0;
    for(int r = 0; r < row; r++){
        getline(file, line);
        for(int c = 0; c < col; c++){
            if(line[c] == 'X') board[r][c] = MARBLE_INVALID;
            else if(line[c] == '-') board[r][c] = MARBLE_EMPTY;
            else if(line[c] == 'O') {
                marbleCount++;
                board[r][c] = MARBLE_OCCUPIED;
            }
        }
    }
    return marbleCount;
}

void setUpDefaultBoard(Grid<MarbleType>& board){
    for (int row = 0; row < board.numRows(); row++){
        for (int col = 0; col < board.numCols(); col++){
            if ((row < 2 && col < 2) || (row < 2 && col > 4)
             || (row > 4 && col < 2) || (row > 4 && col > 4)){
                board[row][col] = MARBLE_INVALID;
            }
            else{
                board[row][col] = MARBLE_OCCUPIED;
            }
        }
    }
    //Remove the very center marble
    board[3][3] = MARBLE_EMPTY;
}
