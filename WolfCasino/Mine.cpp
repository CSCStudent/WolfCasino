/*
Copyright (c) 2023 Hridaya Bijayananda
Author: Hridaya Bijayananda
*/

#include "Mine.h"

using namespace MS;

Mine::Mine()
{
	this->mineNum = mineNum;
}
// Post-condition: Creates a Mine class object

Mine::~Mine()
{}
// Post-condition: destroys a Mine class object

// Pre-condition: An array of mines, the board, the mineNum, and the boardSize are passed in as arguments
void Mine::putMine(int mines[][two], char board[][MAX_SIZE], int mineNum, int boardSize)
{
	bool mine[MAX_SIZE * MAX_SIZE];
	memset(mine, false, sizeof(mine));

	for (int i = zero; i < mineNum;)
	{
		int randomNum = rand() % (boardSize * boardSize);
		int x = randomNum / boardSize;
		int y = randomNum % boardSize;

		if (mine[randomNum] == false)
		{
			mines[i][0] = x;
			mines[i][1] = y;

			int loc1 = mines[i][0];
			int loc2 = mines[i][1];

			board[loc1][loc2] = 'ten';
			mine[randomNum] = true;
			i++;
		}
	}
	return;
}
// Post-condition: Randomly places the mines on the board