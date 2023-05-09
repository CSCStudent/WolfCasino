#pragma once
#include "Casino.h"
#include "CheckersPlayer.h"
#include "CheckersPawn.h"

namespace S02257117 {
    class checkers : public CSC2034::Casino {
    public:
        checkers();

        static checkers* makeGame();

        //This plays the game
        void start();

    private:
        void run();
        void printBoard();  // the function used to neatly display the board to the console.
        void fillBoard();  // fills the board with the starting pieces for both players. 
        int move(CheckersPlayer); // The function for the players to move their pieces and capture pieces. returns playerscore
        bool moveCheckF(int, int, int, int, CheckersPlayer);

        pawn board[8][8]; // a 2D array playing board

    };
}