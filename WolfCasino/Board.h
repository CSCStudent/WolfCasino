/*
Copyright (c) 2023 Hridaya Bijayananda
Author: Hridaya Bijayananda
*/

#ifndef Board_H
#define Board_H

#include <iostream>
#include "MineSweeper.h"

using namespace std;
//using namespace MS;

namespace MS
{
	class Board
	{
	public:
		int boardSize;
		Board();
		Board(int);
		~Board();
		char board[MAX_SIZE][MAX_SIZE];
		void printBoard(char[][MAX_SIZE], int);
	};

}

#endif // !BOARD_H