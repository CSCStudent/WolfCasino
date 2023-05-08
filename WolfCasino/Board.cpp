/*
Copyright (c) 2023 Hridaya Bijayananda
Author: Hridaya Bijayananda
*/

#include "Board.h"
using namespace MS;

Board::Board()
{
	this->boardSize = boardSize;
}
// Post-condition: Creates a Board class object

// Pre-condition: The size of the board is taken as an argument
Board::Board(int size)
{
	boardSize = size;
	// Initialize the board with empty cells
	for (int i = 0; i < boardSize; i++)
	{
		for (int j = 0; j < boardSize; j++)
		{
			board[i][j] = '.';
		}
	}
}
// Post-condition: Creates a Board class object and initializes the board

Board::~Board()
{}
// Post-condition: Destroys a Board class object

// Pre-condition: The board and the boardSize are passed in as arguments
void Board::printBoard(char makeBoard[][MAX_SIZE], int boardSize)
{
	printf("\t");
	for (int i = 0; i < boardSize; i++)
	{
		printf("%2d ", i);
	}
	printf("\n\n");
	for (int i = 0; i < boardSize; i++)
	{
		printf("%d\t", i);
		for (int j = 0; j < boardSize; j++)
		{
			if (makeBoard[i][j] == '0')
			{
				printf("%2c ", ' ');
			}
			else if (makeBoard[i][j] == 'e')
			{
				printf("%2c ", '>');
			}
			else if (makeBoard[i][j] == 'n')
			{
				printf("%2c ", '.');
			}
			else if (makeBoard[i][j] != 'n' && makeBoard[i][j] != 'e' && makeBoard[i][j] != '0')
			{
				printf("%2c ", makeBoard[i][j]);
			}
		}
		printf("\n");
	}
	return;
}
// Post-condition: The board is printed