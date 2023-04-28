#include "roulette.h"
#include <iostream>
#include <stdlib.h> //random nums
#include <stdio.h>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <fstream>
#include <ctime>

//sleep function for cross platform, found on stackoverflow, link: https://stackoverflow.com/questions/6649936/c-compiling-on-windows-and-linux-ifdef-switch
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#define Sleep(x) usleep((x)*1000)   //defines Sleep() for cross platform use
#endif

//S02987215
namespace CSC2034 {
    Roulette::Roulette() {
        //initalize wheel values
        std::string fIn;
        std::cout << "For optimal experience extend window to fit the #'s below all on one line\n";
        std::cout << "#####################################################################################################################################################\n\n";       
        std::cout << "Input file name for wallet, write 'd' if you want to default to \"rouletteWallet.txt\": ";
        std::cin >> fIn;
        if(fIn == "d") {
            setFile("rouletteWallet.txt");
        }
        else {
            setFile(fIn);
        }
        setRolls();
        srand(time(NULL)); //initialze srand with time
    }
    Roulette::~Roulette() {}

    /**************************************************************************
     *   roll: roll the wheel, select random num on the wheel, and subtract bet from wallet, add to wallet if it is a win
     *   Pre-condition: Input must be int on the wheel, wallet must have enough to bet
     *   Post-condition: none
     **************************************************************************/
    void Roulette::roll(int bet, int betIndex) {
        if(validBet(bet)) {
            int wf = getWallet();
            wf -= bet;                          //subtract bet from wallet

            int rollIndex = rand() % NUMBERS;   //find index of roll with NUMBERS const val
            const int rollTime = 25;  //set rollTime to 25
            auto tempWheel = wheel;             //create temp vector for rotating the wheel
            std::string ballStr(NUMBERS*5, ' ');//create string long enough to display where the ball lands
            
            Sleep(2000);
            
            for(int i = 0; i < rollTime; i++) {
                //| 27| 10| 25| 29| 12| 8 | 19| 31| 18| 6 | 21| 33| 16| 4 | 23| 35| 14| 2 | 0 | 28| 9 | 26| 30| 11| 7 | 20| 32| 17| 5 | 22| 34| 15| 3 | 24| 36| 13| 1 |
                //ball will show below the number, if 17 is determined, it will show here   o
                Sleep(100 + (i*10)); //slow rotation for each loop
                std::rotate(tempWheel.begin(), tempWheel.begin()+1, tempWheel.end());
                Roulette::Clear();
                printBoard();
                std::cout << "\nYour bet is " << bet << " on " << getBetStr(betIndex) << "\n\nRolling...\n";
                std::cout << "|";
                for(auto val : tempWheel) {
                    std::cout << ' ' << ((val < 10) ? (std::to_string(val) + " ") : std::to_string(val)) << "|";   //format output to be 2 wide for each number
                }
            }
            int winNum = tempWheel[rollIndex];
            auto it = find(tempWheel.begin(), tempWheel.end(), winNum);
            int wheelIndex = ((it-tempWheel.begin())*4)+2;
            ballStr[wheelIndex] = 'o';
            std::cout << '\n' << ballStr << '\n';// << "Should be: " << winNum << " and index is " << wheelIndex << '\n'; //test code to check ball is correctly placed
            addRoll(winNum);
            std::cout << "The ball landed on \"" << winNum << "\" above...\n";
            if(checkWin(betIndex, winNum)) {
                wf += getWinnings(betIndex, bet);
                std::cout << "You won! You now have " << wf << " credits\n\n";
            }
            else {
                std::cout << "You lost. You now have " << wf << " credits\n\n"; 
            }
            setWallet(wf);
        }
        else {
            std::cout << "Invalid bet, not enough in wallet\n";
        }
    }

    /**************************************************************************
     *   getRolls: prints previous 10 rolls
     *   Pre-condition: none
     *   Post-condition: none
     **************************************************************************/
    void Roulette::getRolls() {
        if(!prevRolls.empty()) {
            for(int roll : prevRolls) {
                std::cout << roll << ' ';
            }
            std::cout << '\n';
        }
        else {
            std::cout << "No previous rolls\n";
        }
    }

    /**************************************************************************
     *   deposit: adds int value to wallet
     *   Pre-condition: int input must be > 0
     *   Post-condition: none
     **************************************************************************/
    void Roulette::deposit(int dep) {
        try {
            if(dep > 0) {
                int wd = getWallet() + dep;
                setWallet(wd);
                std::cout << "You now have " << wd << " credits in your wallet\n";
            }
            else {
                throw dep;
            }
        }
        catch (int num) {
            std::cout << "Incorrect deposit amount of " << num << '\n';
        }
    }

    bool Roulette::validBet(int bet) {
        return (bet <= getWallet()) ? true : false;
    }

    std::string Roulette::getBetStr(int num) {
        std::string retStr;
        if(num >= 0 && num <= 36) {
            return std::to_string(num);
        }
        else if(num >= 37 && num <= 39) {
            switch(num) {
                case 37:
                    retStr = "top row";
                    break;
                case 38:
                    retStr = "middle row";
                    break;
                case 39:
                    retStr = "bottom row";
                    break;
            }
        }
        else if(num >= 40 && num <= 42) {
            switch(num) {
                case 40:
                    retStr = "the 1st 12";
                    break;
                case 41:
                    retStr = "the 2nd 12";
                    break;
                case 42:
                    retStr = "the 3rd 12";
                    break;
            }
        }
        else if(num >= 43 && num <= 48) {
            switch(num) {
                case 43:
                    retStr = "1 to 18";
                    break;
                case 44:
                    retStr = "EVENS";
                    break;
                case 45:
                    retStr = "RED";
                    break;
                case 46:
                    retStr = "BLACK";
                    break;
                case 47:
                    retStr = "ODDS";
                    break;
                case 48:
                    retStr = "19 to 36";
                    break;
            }
        }
        else {
            retStr = "Invalid bet, no matching bets for [" + std::to_string(num) + "]";
        }
        return retStr;
    }

    void Roulette::printBoard() {
    /*  board and indexes (numbers in brackts [] are the index that player will input)
            /---|----------------------------|---------------------------------|-------------------------------|----------|
        /     |3[3]   6[6]   9[9]  12[12]  | 15[15]  18[18]  21[21]  24[24]  | 27[27]  30[30]  33[33]  36[36]| 2TO1[37] |
        /       |----------------------------|---------------------------------|-------------------------------|----------|
    |  0[0]  |2[2]   5[5]   8[8]  11[11]  | 14[14]  17[17]  20[20]  23[23]  | 26[26]  29[29]  32[32]  35[35]| 2TO1[38] |
        \       |----------------------------|---------------------------------|-------------------------------|----------|
        \     |1[1]   4[4]   7[7]  10[10]  | 13[13]  16[16]  19[19]  22[22]  | 25[25]  28[28]  31[31]  34[34]| 2TO1[39] |
            \---|----------------------------|---------------------------------|-------------------------------|----------|
                |         1st12[40]          |           2nd12[41]             |           3rd12[42]           |
                |-------------|--------------|---------------|-----------------|--------------|----------------|
                |  1to18[43]  |   EVEN[44]   |     RED[45]   |   BLACK[46]     |    ODD[47]   |   19to36[48]   |
                |-------------|--------------|---------------|-----------------|--------------|----------------|
    */
        Roulette::Clear();  //clear terminal first
        std::cout << "\n\nUsing the board below select which bet, and how much, you would like to place\n(use the numbers in the brackets for which bet you want to place)\nFor example: entering 5 then 45 means I placed 5 credits on RED\n\n";
        std::cout << "You currently have " << getWallet() << " credits\n\n";
        std::cout << "        /---|----------------------------|---------------------------------|-------------------------------|----------|\n";
        std::cout << "      /     |\033[31m3[3]\033[0m   6[6]   \033[31m9[9]\033[0m  \033[31m12[12]\033[0m  | 15[15]  \033[31m18[18]\033[0m  \033[31m21[21]\033[0m  24[24]  | \033[31m27[27]\033[0m  \033[31m30[30]\033[0m  33[33]  \033[31m36[36]\033[0m| \033[32m2TO1[37]\033[0m |\n";
        std::cout << "    /       |----------------------------|---------------------------------|-------------------------------|----------|\n";
        std::cout << "   |  \033[32m0[0]\033[0m  |2[2]   \033[31m5[5]\033[0m   8[8]  11[11]  | \033[31m14[14]\033[0m  17[17]  20[20]  \033[31m23[23]\033[0m  | 26[26]  29[29]  \033[31m32[32]\033[0m  35[35]| \033[32m2TO1[38]\033[0m |\n";
        std::cout << "    \\       |----------------------------|---------------------------------|-------------------------------|----------|\n";
        std::cout << "      \\     |\033[31m1[1]\033[0m   4[4]   \033[31m7[7]\033[0m  10[10]  | 13[13]  \033[31m16[16]\033[0m  \033[31m19[19]\033[0m  22[22]  | \033[31m25[25]\033[0m  28[28]  31[31]  \033[31m34[34]\033[0m| \033[32m2TO1[39]\033[0m |\n";
        std::cout << "        \\---|----------------------------|---------------------------------|-------------------------------|----------|\n";
        std::cout << "            |         \033[32m1st12[40]\033[0m          |           \033[32m2nd12[41]\033[0m             |           \033[32m3rd12[42]\033[0m           |\n";
        std::cout << "            |-------------|--------------|---------------|-----------------|--------------|----------------|\n";
        std::cout << "            |  \033[32m1to18[43]\033[0m  |   \033[32mEVEN[44]\033[0m   |    \033[31mRED[45]\033[0m    |    BLACK[46]    |    \033[32mODD[47]\033[0m   |   \033[32m19to36[48]\033[0m   |\n";
        std::cout << "            |-------------|--------------|---------------|-----------------|--------------|----------------|\n\n";
        std::cout << "The previous 10 rolls were: ";
        printPrevRolls();
    }

    void Roulette::getBet(int& amt, int& ind) {
        std::cout << "Input bet amount: ";
        std::cin >> amt;
        std::cout << "\nInput which bet you would like to place (write the number inside the brackets on the board above): ";
        std::cin >> ind;
    }

    bool Roulette::checkWin(int bi, int winner) {
        bool bOut = false;
        if(winner == bi) {
            bOut = true;
        }
        else if(bi >= 37 && bi <= 39) {
            for(int i = 0; i < 12; i++) {
                if(winner == ((i*3)+(40-bi))) { //depending on row selected, if winner is part of this row its a win
                    bOut = true;
                }
            }
        }
        else if(bi >= 40 && bi <= 42) {
            if(winner >= (12*(bi-40))+1  && winner <= 12*(bi-39)) { //bi == 40 --> (1 <= winner <= 12) | bi == 41 --> (13 <= winner <= 24) | bi == 42 -> (25 <= winner <= 46)
                bOut = true;
            }
        }
        else if(bi >= 43 && bi <= 48) {
            switch(bi) {
                case 43:
                    bOut = (winner >= 1 && winner <= 18) ? true : bOut;
                    break;
                case 44:
                    bOut = (winner % 2 == 0) ? true : bOut;
                    break;
                case 45:
                    for(auto rd : REDS) {
                        if(rd == winner) {
                            bOut = true;
                        }
                    }
                    break;
                case 46:
                    for(auto bl : BLACKS) {
                        if(bl == winner) {
                            bOut = true;
                        }
                    }
                    break;
                case 47:
                    bOut = (winner % 2 != 0) ? true : bOut;
                    break;
                case 48:
                    bOut = (winner >= 19 && winner <= 36) ? true : bOut;
                    break;
            }
        }
        return bOut;
    }

    int Roulette::getWinnings(int num, int b) {
        int winnings = 0;
        if(num >= 0 && num <= 36) {
            winnings = b*36;
        }
        else if(num >= 37 && num <= 42) {
            winnings = b*3;
        }
        else if(num >= 43 && num <= 48) {
            winnings = b*2;
        }
        return winnings;
    }

    void Roulette::Clear()
    {
        #if defined _WIN32
            system("cls");  //windows uses different clear command than other systems, so check if machine is windows
        #else
            system("clear");
        #endif
    }

    void Roulette::setFile(std::string fStr) {

        dFile.open(fStr, std::ios::in | std::ios::out);  //initialize file to fStr (file name)

        if(dFile.good()) {      //is the file readable?
            setWallet();
        }
        else {
            std::cerr << "Error: File could not be read\n";
        }
    }

    void Roulette::setWallet(int wal) {
        
        dFile.clear();  //overwrite and set wallet to 0
        dFile.seekp(0);
        dFile << wal << std::endl;
    }

    void Roulette::setWallet() {
        int tempnum;
        if(dFile >> tempnum) {  //does file have one integer in it already?
                int testnum;
                if(dFile >> testnum) {  //does file have more than one integer in it?
                    dFile.clear();  //overwrite and set wallet to 0
                    dFile.seekp(0);
                    dFile << 0 << std::endl;         //if yes, overwrite and set wallet to 0
                }
                else {}     //file contains one integer, which is used for the wallet value, and means it is a returning user
            }
            else {
                std::cout << "\n\nhere\n\n";
                dFile.clear();  //overwrite and set wallet to 0
                dFile.seekp(0);
                dFile << 0 << std::endl;
            }
    }
    int Roulette::getWallet() {
        int wf;
        dFile.clear();
        dFile.seekg(0, std::ios::beg);
        dFile >> wf;
        return wf;
    }

    void Roulette::setRolls() {
        for(int i = 0; i < 10; i++) {
            int rn = rand() % NUMBERS;
            prevRolls.push_back(rn); //int rollIndex = rand() % NUMBERS;
        }
    } 

    void Roulette::addRoll(int roll) {
        if(prevRolls.size() == 10) {
            prevRolls.erase(prevRolls.begin());
        }
        prevRolls.push_back(roll);
    }

    void Roulette::printPrevRolls() {
        for(int roll : prevRolls) {
            std::string rollStr = std::to_string(roll);
            for(int red : REDS) {
                if(roll == red) {
                    rollStr = "\033[31m" + rollStr + "\033[0m";
                }
            }
            std::cout << "| " << rollStr << " ";
        }
        std::cout << "|\n\n";
    }

    void Roulette::start() {
        char in;
        int betAmt;
        int betIndex;
        bool start = false;
        std::cout << "Welcome to Roulette!\n\n";
        while(true) {
            std::cout << "Please select a function and type the respective letter:\n(D) Deposit | (R) Roll and place bets | (W) Wallet | (Q) Quit | Input: ";
            std::cin >> in;
            switch(in) {
                case 'D':
                case 'd':
                    std::cout << "\nInput deposit amount: ";
                    std::cin >> betAmt;
                    deposit(betAmt);
                    std::cout << '\n';
                    break;
                case 'R':
                case 'r':
                    printBoard();
                    getBet(betAmt, betIndex);
                    roll(betAmt, betIndex);
                    break;
                case 'W':
                case 'w':
                    std::cout << "\nYou currently have " << getWallet() << " credits\n\n";
                    break;
                case 'Q':
                case 'q':
                    exit(1);
                    break;
                default:
                    std::cout << "\n\nInvalid function, try again\n\n";
            }
        }
    }

    /**************************************************************************
    *   makeGame: returns Roulette object type for Casino use
    *   Pre-condition: none
    *   Post-condition: none
    **************************************************************************/
    Roulette* Roulette::makeGame() {
        return new Roulette;
    }
}