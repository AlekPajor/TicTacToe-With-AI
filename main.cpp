#include <iostream>
#include "Game.hpp"

const int SIZE = 3;
const int BOT_DEPTH = 4;


int main(int argc, char *argv[]) {
    Game game(SIZE);
    system("cls");
    do {
        game.move(game.minmax(BOT_DEPTH, 'O'), 'O');
        game.printBoard();
        if(game.isGameOver()) break;
        game.inputMove();
        system("cls");
    } while (true);

    return 0;
}