#pragma once
#include <ctime>
#include "Casino.h"

namespace CSC2034
{
    class TicTacToeGame : public Casino
    {
    public:
        //Constructor
        TicTacToeGame();

        static TicTacToeGame* makeGame();

        //This plays the game
        void start();

    private:
        //Gets input from the user
        int getXCoord(char);
        int getYCoord(char);
        //Places a marker. If it returns false, it couldnt place!
        bool placeMarker(int x, int y, char currentPlayer);

        //Returns true if the current player won!
        bool checkForVictory(char currentPlayer);

        //Empties the board
        void clearBoard();
        // Prints the board
        void printBoard();

        void run();

        //This stores the board state
        char board[3][3];
    };
} //end of namespace