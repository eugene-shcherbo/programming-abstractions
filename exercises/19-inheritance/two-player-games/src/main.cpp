#include <iostream>
#include "console.h"
#include "simpio.h"
#include "nimgame.h"
#include "tictactoegame.h"

using namespace std;

TwoPlayerGameBase* createGame(int userChoose);

int main() {
    std::cout << "Hello! Which game do you want to play? " << std::endl;
    std::cout << "----1. Nim game" << std::endl;
    std::cout << "----2. Tic Tac Toe game" << std::endl;

    int choose = getIntegerBetween("Your choice? ", 1, 2);
    TwoPlayerGameBase* game = createGame(choose);
    game->play();

    return 0;
}

TwoPlayerGameBase* createGame(int userChoose) {
    switch (userChoose) {
        case 1: return new NimGame(13, HUMAN);
        case 2: return new TicTacToeGame();
        default: throw "unknown option";
    }
}
