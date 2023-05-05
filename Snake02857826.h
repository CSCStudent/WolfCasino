#pragma once
#include "SegmentHeader02857826.h"
#include <windows.h>
#include <iostream>
#include <vector>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include "Casino.h"

namespace CSC2034 {
	class Snake02857826 : public Casino {
	private:
		static const int BOARD_HEIGHT = 15;
		static const int BOARD_WIDTH = 30;
		const int SPEED_MULT = 10;
		const int BASE_SPEED = 200;
		const int START_Y = 7;
		const int START_X = 15;
		int score = 0;
		char snakeBoard[BOARD_HEIGHT][BOARD_WIDTH];
		std::vector<Segment02857826> snake;
	public:
		Snake02857826();
		~Snake02857826();
		static Snake02857826* makeGame();
		void populateBoardArray(char(*snakeBoard)[BOARD_HEIGHT][BOARD_WIDTH]);
		void printBoard(char(*snakeBoard)[BOARD_HEIGHT][BOARD_WIDTH]);
		void cycleSnakeArray();
		void addFood();
		void addSegment();
		void start();
		void play();
		char direction();
		int speed();
		bool right();
		bool left();
		bool up();
		bool down();
	};
}