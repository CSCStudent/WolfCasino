#ifndef ROULETTE_H
#define ROULETTE_H

#include <vector>
#include <array>
#include <iostream>
#include <fstream>
#include "Casino.h"

namespace CSC2034 {
    class Roulette : public Casino {
        private:
            const int NUMBERS = 37;     //number of numbers on the wheel
            const int REDS[18] = {32, 19, 21, 25, 34, 27, 36, 30, 23, 5, 16, 1, 14, 9, 18, 7, 12, 3};
            const int BLACKS[18] = {15, 4, 2, 17, 6, 13, 11, 8, 10, 24, 33, 20, 31, 22, 29, 28, 35, 26};
            std::vector<int> wheel = {27, 10, 25, 29, 12, 8, 19, 31, 18, 6, 21, 33, 16, 4, 23, 35, 14, 2, 0, 28, 9, 26, 30, 11, 7, 20, 32, 17, 5, 22, 34, 15, 3, 24, 36, 13, 1};     //vector that holds the wheel
            std::vector<int> prevRolls; //vector that holds the previous 10 rolls
            std::fstream dFile;              //fstream to read/write to

            /**************************************************************************
            *   setFile: sets data file using fstream type using the string of the file name that is input
            *   Pre-condition: none
            *   Post-condition: will overwrite the file if it isn't valid (has one integer for wallet value)
            **************************************************************************/ 
            void setFile(std::string);

            bool validBet(int);         //returns true if theres enough in the wallet for the bet
            std::string getBetStr(int); //based on int input, return string referring to what bet they placed
            void Clear();               //function to clear the screen cross platform from stackoverflow, link: https://stackoverflow.com/questions/6486289/how-can-i-clear-console

            /**************************************************************************
            *   roll: roll the wheel, select random num on the wheel, and subtract bet from wallet, add to wallet if it is a win
            *   Pre-condition: Input must be int on the wheel, wallet must have enough to bet
            *   Post-condition: none
            **************************************************************************/ 
            void roll(int, int);

            /**************************************************************************
            *   getRolls: prints previous 10 rolls
            *   Pre-condition: none
            *   Post-condition: none
            **************************************************************************/
            void getRolls();

            /**************************************************************************
            *   deposit: adds int value to wallet
            *   Pre-condition: int input must be > 0
            *   Post-condition: none
            **************************************************************************/
            void deposit(int);

            /**************************************************************************
            *   printBoard: prints roulette board
            *   Pre-condition: none
            *   Post-condition: none
            **************************************************************************/
            void printBoard();
            
            /**************************************************************************
            *   getBet: gets bet amount and which bet was placed
            *   Pre-condition: none
            *   Post-condition: must have 2 integer inputs from cin
            **************************************************************************/
            void getBet(int&, int&);

            /**************************************************************************
            *   checkWin: returns true or false if you won your bet, compares your bet to winning bet
            *   Pre-condition: int input must be between 0 and 48
            *   Post-condition: none
            **************************************************************************/
            bool checkWin(int, int);

            /**************************************************************************
            *   getBet: calculates winnings based on bet amount and where your bet was placed
            *   Pre-condition: placed bet input must be between 0 and 48
            *   Post-condition: none
            **************************************************************************/
            int getWinnings(int, int);

            /**************************************************************************
            *   setWallet(int): sets wallet value in file
            *   setWallet(): sets wallet to default value 0 unless it contains one integer for wallet value
            *   Pre-condition: setFile called to set fstream
            *   Post-condition: will overwrite the file
            **************************************************************************/
            void setWallet(int);
            void setWallet();

            /**************************************************************************
            *   getWallet: gets wallet value in file
            *   Pre-condition: fstream has been set
            *   Post-condition: none
            **************************************************************************/
            int getWallet();

            /**************************************************************************
            *   setFRolls: sets prev rolls vector with 10 random rolls
            *   Pre-condition: none
            *   Post-condition: will overwrite the file
            **************************************************************************/
            void setRolls();
            
            /**************************************************************************
            *   addRoll: removes oldest elemnt from prevRolls and adds the int input
            *   Pre-condition: none
            *   Post-condition: none
            **************************************************************************/
            void addRoll(int);

            /**************************************************************************
            *   printPrevRolls: prints prev rolls with corrected colors
            *   Pre-condition: assumes prevRolls has 10 rolls inside already
            *   Post-condition: none
            **************************************************************************/
            void printPrevRolls();

        public:
            Roulette();
            ~Roulette();

            /**************************************************************************
            *   start: runs game control code
            *   Pre-condition: none
            *   Post-condition: none
            **************************************************************************/
            void start();

            /**************************************************************************
            *   makeGame: returns Roulette object type for Casino use
            *   Pre-condition: none
            *   Post-condition: none
            **************************************************************************/
            static Roulette* makeGame();
    };
}

#endif