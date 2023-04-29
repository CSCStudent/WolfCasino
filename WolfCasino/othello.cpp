#include "othello.h"

namespace CSC2034 {

    othello* othello::makeGame() {
        return new othello;
    }

    //The game!
    void othello::start() {
        run();
    }

    othello::othello() {}

    othello::~othello() {}

    bool othello::placeToken(int arr[3]) {
        int row = arr[0];
        int col = arr[1];
        int player = arr[2];

        //Check to see if the space is empty
        if (gameBoard[row][col] != 0) {
            return false;
        }

        //Check to see if it is a valid spot and will capture any pieces
        int opponent = (player == 1) ? 2 : 1;
        bool captures = false;
        for (int xOffset = -1; xOffset <= 1; xOffset++) {
            for (int yOffset = -1; yOffset <= 1; yOffset++) {
                if (xOffset == 0 && yOffset == 0) {
                    continue;
                }

                int r = row + yOffset;
                int c = col + xOffset;
                bool capturesInThisDirection = false;
                while (r >= 0 && r < 8 && c >= 0 && c < 8 && gameBoard[r][c] == opponent) {
                    capturesInThisDirection = true;
                    r += yOffset;
                    c += xOffset;
                }
                //switch token colors
                if (capturesInThisDirection && r >= 0 && r < 8 && c >= 0 && c < 8 && gameBoard[r][c] == player) {
                    captures = true;
                    r -= yOffset;
                    c -= xOffset;
                    while (r != row || c != col) {
                        gameBoard[r][c] = player;
                        r -= yOffset;
                        c -= xOffset;
                    }
                }
            }
        }

        //Place token and return true or return that the move was invalid
        if (captures) {
            gameBoard[row][col] = player;
            return true;
        }
        else {
            return false;
        }
    }

    void othello::print() {

        SetConsoleTextAttribute(hConsole, 42);
        cout << (char)201 << (char)205 << (char)205 << (char)203 << (char)205 << (char)205 << (char)203 << (char)205 << (char)205 << (char)203 << (char)205 << (char)205 << (char)203 << (char)205 << (char)205 << (char)203 << (char)205 << (char)205 << (char)203 << (char)205 << (char)205 << (char)203 << (char)205 << (char)205 << (char)187 << endl;
        for (int i = 0; i < 8; i++) {
            cout << (char)186;
            for (int j = 0; j < 8; j++) {
                gameBoard[i][j] == 2 ? SetConsoleTextAttribute(hConsole, 32) : gameBoard[i][j] == 1 ? SetConsoleTextAttribute(hConsole, 39) : SetConsoleTextAttribute(hConsole, 34);
                cout << (char)219 << (char)219;
                SetConsoleTextAttribute(hConsole, 42);
                cout << (char)186;
            }
            cout << endl;
            if (i != 7) { cout << (char)204 << (char)205 << (char)205 << (char)206 << (char)205 << (char)205 << (char)206 << (char)205 << (char)205 << (char)206 << (char)205 << (char)205 << (char)206 << (char)205 << (char)205 << (char)206 << (char)205 << (char)205 << (char)206 << (char)205 << (char)205 << (char)206 << (char)205 << (char)205 << (char)185 << endl; }
        }
        cout << (char)200 << (char)205 << (char)205 << (char)202 << (char)205 << (char)205 << (char)202 << (char)205 << (char)205 << (char)202 << (char)205 << (char)205 << (char)202 << (char)205 << (char)205 << (char)202 << (char)205 << (char)205 << (char)202 << (char)205 << (char)205 << (char)202 << (char)205 << (char)205 << (char)188 << endl;
        SetConsoleTextAttribute(hConsole, 7);
    }

    void othello::updateScore() {
        whiteScore = 0;
        blackScore = 0;
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                gameBoard[i][j] == 1 ? whiteScore++ : gameBoard[i][j] == 2 ? blackScore++ : 0;
            }
        }
    }

    int othello::getScore(int player) {
        if (player == 1) {
            return whiteScore;
        }
        else {
            return blackScore;
        }
    }

    bool othello::checkBoard() {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                if (!gameBoard[i][j]) {
                    return false;
                }
            }
        }
        return true;
    }

    ostream& operator << (ostream& os, othello& game) {
        game.updateScore();
        os << "White: " << game.whiteScore << "           Black: " << game.blackScore << endl;
        SetConsoleTextAttribute(game.hConsole, 42);
        os << "    " << "0" << "  " << "1" << "  " << "2" << "  " << "3" << "  " << "4" << "  " << "5" << "  " << "6" << "  " << "7" << "  " << endl;
        os << "   " << (char)201 << (char)205 << (char)205 << (char)203 << (char)205 << (char)205 << (char)203 << (char)205 << (char)205 << (char)203 << (char)205 << (char)205 << (char)203 << (char)205 << (char)205 << (char)203 << (char)205 << (char)205 << (char)203 << (char)205 << (char)205 << (char)203 << (char)205 << (char)205 << (char)187 << endl;
        for (int i = 0; i < 8; i++) {
            os << " " << i << " " << (char)186;
            for (int j = 0; j < 8; j++) {
                game.gameBoard[i][j] == 2 ? SetConsoleTextAttribute(game.hConsole, 32) : game.gameBoard[i][j] == 1 ? SetConsoleTextAttribute(game.hConsole, 39) : SetConsoleTextAttribute(game.hConsole, 34);
                os << (char)219 << (char)219;
                SetConsoleTextAttribute(game.hConsole, 42);
                os << (char)186;
            }
            os << endl;
            if (i != 7) { os << "   " << (char)204 << (char)205 << (char)205 << (char)206 << (char)205 << (char)205 << (char)206 << (char)205 << (char)205 << (char)206 << (char)205 << (char)205 << (char)206 << (char)205 << (char)205 << (char)206 << (char)205 << (char)205 << (char)206 << (char)205 << (char)205 << (char)206 << (char)205 << (char)205 << (char)185 << endl; }
        }
        os << "   " << (char)200 << (char)205 << (char)205 << (char)202 << (char)205 << (char)205 << (char)202 << (char)205 << (char)205 << (char)202 << (char)205 << (char)205 << (char)202 << (char)205 << (char)205 << (char)202 << (char)205 << (char)205 << (char)202 << (char)205 << (char)205 << (char)202 << (char)205 << (char)205 << (char)188 << endl;
        SetConsoleTextAttribute(game.hConsole, 7);
        return os;
    }

    void othello::run() {

        int arrtest[3] = { 0,0,1 };
        bool invalid = false;

        while (!this->checkBoard()) {
            bool turn = false;
            system("CLS");
            cout << *this;
            if (invalid) {
                cout << "Invalid move try again, if there are no valid moves enter row 8 and column 8 to pass" << endl;
                invalid = false;
            }
            arrtest[2] == 1 ? cout << "White: " << endl : cout << "Black: " << endl;
            cout << "Row(0-7): ";
            cin >> arrtest[0];
            cout << "Column(0-7): ";
            cin >> arrtest[1];
            if ((arrtest[0] != 8) && (arrtest[1] != 8)) {
                turn = this->placeToken(arrtest);
            }
            else {
                turn = true;
            }
            if (turn) {
                int opponent = (arrtest[2] == 1) ? 2 : 1;
                arrtest[2] = opponent;
            }
            else {
                invalid = true;
            }
        }
        system("CLS");
        cout << *this;
        if (this->getScore(1) > this->getScore(2)) {
            cout << "White Player Wins!" << endl;
        }
        else if (this->getScore(2) > this->getScore(1)) {
            cout << "Black Player Wins!" << endl;
        }
        else {
            cout << "Tie Game!" << endl;
        }
        system("pause");
        return;
    }
}