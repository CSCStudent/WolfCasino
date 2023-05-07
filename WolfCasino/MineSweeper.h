/*
Copyright (c) 2023 Hridaya Bijayananda
Author: Hridaya Bijayananda
*/

#ifndef MineSweeper_H
#define MineSweeper_H

#include <iostream>
#include <vector>
#include "Casino.h"
#define MAX_SIZE 25
#define MAX_MINES 99

enum { zero, one = 1, two = 2, three = 3, four = 4, five = 5, six = 6, seven = 7, eight = 8, nine = 9, ten = 10, eleven = 11, sixteen = 16, twentyfive = 25, fourty = 40, ninetynine = 99 };

using namespace std;

namespace CSC2034
{
	class MineSweeper : public Casino
	{
	private:
		bool checkIfMine(int, int, char[][MAX_SIZE]);
		bool gameOver();
		bool examineLocation(int, int, int, char[][MAX_SIZE]);
		bool moveIsValid(int, int, int);
		int countAdjacentMines(int, int, int, char[][MAX_SIZE]);
		void run();
	public:
		bool makeAMove(int, char[][MAX_SIZE]);
		static MineSweeper* makeGame();
		void start();
		MineSweeper();
		~MineSweeper();
	};
}
#endif // !MineSweeper_H