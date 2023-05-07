//
// Created by Lindsey Larson on 5/6/23.
//

#ifndef WOLFCASINO_MASTER_WORDLE_H
#define WOLFCASINO_MASTER_WORDLE_H
#include <iostream>
#include <vector>
#include "Casino.h"

namespace CSC2034 {
    class wordle : public Casino {
    private:

    private:
        size_t wordsize = 0;
        size_t wordDefault = 5;
        size_t guessDefault = 6;
        std::string badChar = ".";
        std::string goodChar = "☺";
        std::string wrongChar = "~";
        std::vector<std::string> words;
        std::string correctWord;
        std::string dictionary;
        std::vector<std::string> output;
        std::string op;

    public:
        wordle() = default;

        static wordle* makeGame();

        void start();

        void run();

        wordle(const wordle& rhs) {
            *this = rhs;
        }

        void add_dict(std::string);

        std::string select_target();

        bool contains(std::string);

        std::string feedback(std::string);

        friend std::ostream& operator<<(std::ostream&, const wordle&);
    };
}
#endif //WOLFCASINO_MASTER_WORDLE_H
