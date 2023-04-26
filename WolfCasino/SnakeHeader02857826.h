//#ifndef SNAKEHEADER02857826.H
//#define SNAKEHEADER02857826.H

#include "SegmentHeader02857826.h"
#include <windows.h>
#include <iostream>
#include <vector>
#include <conio.h>
#include <cctype>

class Snake02857826 {
private:
	static const int BOARD_HEIGHT = 15;
	static const int BOARD_WIDTH = 30;
	const int START_Y = 7;
	const int START_X = 15;
	char snakeBoard[BOARD_HEIGHT][BOARD_WIDTH];
	std::vector<Segment02857826> snake;
public:
	void populateBoardArray(char(*snakeBoard)[BOARD_HEIGHT][BOARD_WIDTH]);
	void printBoard(char(*snakeBoard)[BOARD_HEIGHT][BOARD_WIDTH]);
	bool loss();
	void run();
	void right();
	void left();
	void up();
	void down();
};
//#endif