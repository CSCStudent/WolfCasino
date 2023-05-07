#include <iostream>
#include <ctime>
#include "TicTacToe.h"

namespace CSC2034
{
    //Constructor
    TicTacToeGame::TicTacToeGame()
    {
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                board[i][j] = ' ';

    }

    TicTacToeGame* TicTacToeGame::makeGame() {
        return new TicTacToeGame;
    }

    //The game!
    void TicTacToeGame::start() {
        run();
    }


    void TicTacToeGame::run() {
        clearBoard();

        char player1 = 'X';
        char player2 = 'O';

        char currentPlayer = player1;
        bool isDone = false;

        int x, y;

        int turn = 0;

        //Inner game loop
        while (isDone == false) {

            //Print out the board each time we loop
            printBoard();

            //Get the coordinates of where the user wants to place a marker
            x = getXCoord(currentPlayer);
            y = getYCoord(currentPlayer);

            //Try to place a marker
            if (placeMarker(x, y, currentPlayer) == false) {
                //If we failed to place a marker, tell him he failed!
                std::cout << "That spot is occupied!\n";
            }
            else {
                //Otherwise, we successfully did this turn!
                turn++;
                //See if the player won!
                if (checkForVictory(currentPlayer) == true) {
                    //He won!
                    std::cout << "The game is over! Player " << currentPlayer << " has won!\n";
                    std::cout << "\a\a\a" << std::endl;
                    isDone = true;
                }
                else if (turn == 9) {
                    //Tie game!
                    std::cout << "Its a tie game!\n";
                    isDone = true;
                }

                // Switch players
                if (currentPlayer == player1) {
                    currentPlayer = player2;
                }
                else {
                    currentPlayer = player1;
                }
            }
        }
    }



    int TicTacToeGame::getXCoord(char player)
    {
        bool isInputBad = true;

        int x;

        while (isInputBad == true) {
            std::cout << player << " enter the column coordinate: ";
            std::cin >> x;

            if (x < 1 || x > 3) {
                std::cout << "Invalid Coordinate!\n";
            }
            else {
                isInputBad = false;
            }
        }
        return x - 1;
    }

    int TicTacToeGame::getYCoord(char player)
    {
        bool isInputBad = true;

        int y;

        while (isInputBad == true) {
            std::cout << player << " enter the row coordinate: ";
            std::cin >> y;

            if (y < 1 || y > 3) {
                std::cout << "Invalid Coordinate!\n";
            }
            else {
                isInputBad = false;
            }
        }
        return y - 1;
    }

    bool TicTacToeGame::placeMarker(int x, int y, char currentPlayer)
    {
        if (board[y][x] != ' ') {
            return false;
        }

        board[y][x] = currentPlayer;
        return true;
    }

    bool TicTacToeGame::checkForVictory(char currentPlayer)
    {
        //Check the rows
        for (int i = 0; i < 3; i++) {
            if ((board[i][0] == currentPlayer) && (board[i][0] == board[i][1]) && (board[i][1] == board[i][2])) {
                return true; //We won!
            }
        }

        //Check the columns
        for (int i = 0; i < 3; i++) {
            if ((board[0][i] == currentPlayer) && (board[0][i] == board[1][i]) && (board[1][i] == board[2][i])) {
                return true; //We won!
            }
        }

        //Check top left diagonal
        if ((board[0][0] == currentPlayer) && (board[0][0] == board[1][1]) && (board[1][1] == board[2][2])) {
            return true; //We won!
        }

        //Check top right diagonal
        if ((board[2][0] == currentPlayer) && (board[2][0] == board[1][1]) && (board[1][1] == board[0][2])) {
            return true; //We won!
        }

        return false;
    }

    void TicTacToeGame::clearBoard()
    {
        //Empties the board
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                board[i][j] = ' ';
            }
        }
    }

    void TicTacToeGame::printBoard()
    {
        //ugly formatting yay
        system("cls");
        time_t now = time(0);
       // std::cout << ctime(&now) << std::endl;

        std::cout << std::endl;
        std::cout << " |1 2 3|\n";
        for (int i = 0; i < 3; i++) {
            std::cout << " -------\n";
            std::cout << i + 1 << "|" << board[i][0] << "|" << board[i][1] << "|" << board[i][2] << "|\n";
        }
        std::cout << " -------\n";
    }

} // end of namespace