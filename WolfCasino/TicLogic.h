//
// Created by owencramer on 5/1/2023.
//

#ifndef WOLFCASINO_TICLOGIC_H
#define WOLFCASINO_TICLOGIC_H

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "TicLogic.h"
#include "Casino.h"

using namespace std;

namespace CSC2034 {
    class TicLogic : public Casino {
    public:
        TicLogic(); //constructor
        ~TicLogic(); //destructor

        static TicLogic* makeGame();
        void start();

        void initialize_board();
        void print_board();
        bool check_win(char marker);
        bool check_draw();
        void player_move(char player);
        void computer_move();
        void run();

    };
}



#endif //WOLFCASINO_TICLOGIC_H
