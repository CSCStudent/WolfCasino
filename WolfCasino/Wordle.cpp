//
// Created by Lindsey Larson on 5/6/23.
//
#include "Wordle.h"
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <random>
#include <fstream>

using namespace std;
namespace CSC2034 {

    void wordle::add_dict(string path) {
        vector<char> v(path.begin(), path.end());

        fstream in(path);
        if (!in) {
            cerr << "Can’t open " << path << "\n";
            exit(1);
        }

        for (string line; getline(in, line);) {
            if (line.size() == wordDefault) {
                this->words.push_back(line);
                this->wordsize++;
            }
            for (size_t i = 0; i < words.size(); i++) {
                wordsize++;
            }
        }
        if (wordsize == 0) {
        }
    }

    string wordle::select_target() {
        if (this->words.size() == 0) {
            cerr << "None of the dictionary files contain any words " << this->wordDefault << " characters long.\n";
            exit(1);
        }

        random_device rd;
        size_t ws = this->words.size();
        correctWord.clear();
        this->correctWord = words[rd() % ws];
        return correctWord;
    }

    bool wordle::contains(string word) {
        for (size_t i = 0; i < this->words.size(); i++) {
            if (word == words[i]) {
                return true;
            }
        }
        return false;
    }

    string wordle::feedback(string guess) {
        vector<char> brokenGuess;
        vector<char> brokenAnswer;
        vector<string> input;
        this->op = "";
        size_t counter = 0;
        op.clear();
        output.clear();

        while (counter <= wordDefault && output.size() <= wordDefault) {
            if (this->correctWord == guess) {
                for (size_t i = 0; i < wordDefault; i++) {
                    output.push_back(this->goodChar);
                }
                counter = 100;
                break;
            }
            else {
                input.push_back(guess);
                copy(guess.begin(), guess.end(), std::back_inserter(brokenGuess));
                copy(correctWord.begin(), correctWord.end(), std::back_inserter(brokenAnswer));
                for (size_t i = 0; i < guess.size(); i++) {
                    if (brokenAnswer[i] == brokenGuess[i]) {
                        output.push_back(goodChar);
                        counter++;
                        if (counter == wordDefault) {
                            counter = 100;
                        }
                    }
                    else if (brokenAnswer[i] != brokenGuess[i]) {
                        for (size_t k = 0; k <= guess.size(); k++) {
                            if (brokenGuess[i] == brokenAnswer[k]) {
                                output.push_back(this->wrongChar);
                                counter++;
                                k = 10;
                                if (counter == wordDefault) {
                                    counter = 100;
                                }
                            }
                            else if (k == guess.size() - 1) {
                                output.push_back(this->badChar);
                                counter++;
                                if (counter == wordDefault) {
                                    counter = 100;
                                }
                            }
                        }
                    }
                }
            }
        }
        for (auto const& s : output) {
            op += s;
        }

        return op;
    }

    wordle* wordle::makeGame() {
        return new wordle;
    }

    void wordle::run() {
        add_dict("words.txt");

        bool final = false;
        const auto& target = select_target();
        cout << "Guess the " << target.size() << "-letter word.\n";
        cout << "☺ = this character is correct\n";
        cout << ". = this character is incorrect\n";
        cout << "~ = this character is in the wrong place\n";

        for (int count = 1; count <= 6; ++count) {
            cout << "Guess #" << count << ": ";
            string guess;
            if (!getline(cin, guess))
                break;
            else if (guess.size() != target.size())
                cout << "“" << guess << "” isn’t length " << target.size() << ".\n";
            else if (!contains(guess))
                cout << "“" << guess << "” isn’t in any dictionary.\n";
            else {
                cout << "          " << feedback(guess) << "\n";
                if (guess == target) {
                    cout << "You won!\n";
                    final = true;
                    break;
                }
            }
        }
        if (final == false) {
            cout << "You lost, the word was “" << target << "”.\n";
        }
    }

    void wordle::start() {
        run();
    }

    ostream& operator<<(std::ostream& os, const wordle& g) {
        string s = g.op;
        return os;
    }
}