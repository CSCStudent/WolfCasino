/* Owen Cramer
 * FRCC2034
 * 7 May 2023
 * Main program to run the TicTacToe Game
 * This came offers a way to play with friend and playing against the computer.
 * How the computer works is by selecting a random location on the board if
 * there is space available. Basically the game runs on easy mode for the player against the computer.
 */


#include "TicLogic.h"
#include <thread>
#include <chrono>


namespace CSC2034 {

    TicLogic* TicLogic::makeGame() {
        return new TicLogic;
    }

    // Game Start!
    void TicLogic::start() {
        run();
    }

    TicLogic::TicLogic() {} // Constructor
    TicLogic::~TicLogic() {} // Destructor

    const int boardSize = 3;
    const char player1 = 'X';
    const char player2 = 'O'; // Will substitute with computer if no player2 is available.

    char board[boardSize][boardSize];
    // Generate the board
    void TicLogic::initialize_board() {
        for (int row = 0; row < boardSize; row++) {
            for (int col = 0; col < boardSize; col++) {
                board[row][col] = ' ';
            }
        }
    }
    // Print the board
    void TicLogic::print_board() {
        cout << "-------------\n";
        for (int row = 0; row < boardSize; row++) {
            cout << "|";
            for (int col = 0; col < boardSize; col++) {
                cout << " " << board[row][col] << " |";
            }
            cout << "\n-------------\n";
        }
    }

    bool TicLogic::check_win(char marker) {
        // Check rows
        for (int row = 0; row < boardSize; row++) {
            bool row_win = true;
            for (int col = 0; col < boardSize; col++) {
                if (board[row][col] != marker) {
                    row_win = false;
                    break;
                }
            }
            if (row_win) {
                return true;
            }
        }
        // Check columns
        for (int col = 0; col < boardSize; col++) {
            bool col_win = true;
            for (int row = 0; row < boardSize; row++) {
                if (board[row][col] != marker) {
                    col_win = false;
                    break;
                }
            }
            if (col_win) {
                return true;
            }
        }
        // Check diagonals
        bool diag1_win = true;
        bool diag2_win = true;
        for (int i = 0; i < boardSize; i++) {
            if (board[i][i] != marker) {
                diag1_win = false;
            }
            if (board[i][boardSize - i - 1] != marker) {
                diag2_win = false;
            }
        }
        if (diag1_win || diag2_win) {
            return true;
        }
        return false;
    }

    bool TicLogic::check_draw() {
        for (int row = 0; row < boardSize; row++) {
            for (int col = 0; col < boardSize; col++) {
                if (board[row][col] == ' ') {
                    return false;
                }
            }
        }
        return true;
    }
    // Player Movement
    void TicLogic::player_move(char player) {
        int row, col;
        cout << "Player " << player << " Enter row (1-" << boardSize << "): ";
        cin >> row;
        cout << "Player " << player << " Enter column (1-" << boardSize << "): ";
        cin >> col;
        row--;
        col--;
        if (row < 0 || row >= boardSize || col < 0 || col >= boardSize || board[row][col] != ' ') {
            cout << "Invalid move! Try again.\n";
            player_move(player);
        } else {
            board[row][col] = player;
        }
    }
    // Computer movement if computer player is selected
    void TicLogic::computer_move() {
        srand(time(NULL));
        int row, col;
        do {
            row = rand() % boardSize;
            col = rand() % boardSize;
        } while (board[row][col] != ' ');
        cout << "Computer plays row " << row + 1 << " column " << col + 1 << ".\n"; // We add 1 to the row and col because arrays technically start at 0.
        board[row][col] = player2;
    }


    void TicLogic::run() { // Main runner for TicTacToe
        int choice;
        cout << "Welcome to TicTacToe!\n";
        cout << "How would you like to play?\n"
                "Play against another player or against the computer?\n"
                "[1 for player, 2 for computer]: ";
        cin >> choice;

        if (choice == 1) {
            initialize_board();
            print_board();
            while (true) {
                // Player1's turn
                cout << "Player " << player1 << endl;
                player_move(player1);
                print_board();
                if (check_win(player1)) {
                    cout << "Player " << player1 << " wins!\n";
                    break;
                }
                if (check_draw()) {
                    cout << "It's a draw!\n";
                    break;
                }
                this_thread::sleep_for(chrono::milliseconds(1000));

                //Player2's turn
                cout << "Player " << player2 << endl;
                player_move(player2);
                print_board();
                if (check_win(player2)) {
                    cout << "Player " << player2 << " wins!\n";
                    break;
                }
                if (check_draw()) {
                    cout << "It's a draw!\n";
                    break;
                }
                this_thread::sleep_for(chrono::milliseconds(1000));
            }

        } else if (choice == 2) {
            initialize_board();
            print_board();
            while (true) {
                player_move(player1);
                print_board();
                if (check_win(player1)) {
                    cout << "You win!\n";
                    break;
                }
                if (check_draw()) {
                    cout << "It's a draw!\n";
                    break;
                }
                this_thread::sleep_for(chrono::milliseconds(1000));
                computer_move();
                print_board();
                if (check_win(player2)) {
                    cout << "Computer wins!\n";
                    break;
                }
                if (check_draw()) {
                    cout << "It's a draw!\n";
                    break;
                }
                this_thread::sleep_for(chrono::milliseconds(1000));
                system("CLS");
            }
        }
    }
}
