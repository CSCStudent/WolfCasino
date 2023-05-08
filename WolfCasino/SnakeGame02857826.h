#include "Snake02857826.h"
#include <windows.h>
#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include "Casino.h"

namespace CSC2034 {
	class SnakeGame02857826 : public Casino {
	private:
		static const int BOARD_HEIGHT = 15;
		static const int BOARD_WIDTH = 30;
		const int SPEED_MULT = 10;
		const int BASE_SPEED = 200;
		int score = 0;
		char snakeBoard[BOARD_HEIGHT][BOARD_WIDTH];
		Snake02857826 snake;
		void populateBoardArray(char(*snakeBoard)[BOARD_HEIGHT][BOARD_WIDTH]);
		void printBoard(char(*snakeBoard)[BOARD_HEIGHT][BOARD_WIDTH]);
		bool isGameOver(char);
		bool foodDetected(char);
		char direction(char);
		void addFood();
		int speed();
		void play();
	public:
		static SnakeGame02857826* makeGame();
		SnakeGame02857826();
		void start();
	};
}
