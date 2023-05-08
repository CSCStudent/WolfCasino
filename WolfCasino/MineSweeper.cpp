/*
Copyright (c) 2023 Hridaya Bijayananda
Author: Hridaya Bijayananda
*/

#include "MineSweeper.h"
#include "Board.h"
#include "Mine.h"
#include "Level.h"

using namespace CSC2034;
using namespace MS;

MineSweeper* MineSweeper::makeGame() 
{
	return new MineSweeper;
}


void MineSweeper::start() 
{
	run();
}

void MineSweeper::run()
{
	Board board;	
	Level level;
	Mine mine;

	char myBoard[MAX_SIZE][MAX_SIZE];


	cout << "Welcome to MineSweeper" << endl << endl;

	bool gameOver = false;

	int boardSize = level.chooseLevel();
	int mineNum = zero;
	(boardSize == nine ? mineNum = ten : NULL);
	(boardSize == sixteen ? mineNum = fourty : NULL);
	(boardSize == twentyfive ? mineNum = ninetynine : NULL);

	Board brd(boardSize);

	int mines[MAX_MINES][two];
	mine.putMine(mines, brd.board, mineNum, boardSize);

	while (gameOver == false)
	{
		brd.printBoard(brd.board, boardSize);
		gameOver = makeAMove(boardSize, brd.board);
	}
	return;
}
MineSweeper::MineSweeper()
{}
// Post-condition: Creates a MineSweeper class object

MineSweeper::~MineSweeper()
{}
// Post-condition: Destroys a MineSweeper class object

// Precondition: The boardSize and the board are passed in as arguments
bool MineSweeper::makeAMove(int boardSize, char board[][MAX_SIZE])
{
	int row, column;
	char choice;
	cout << endl << "Enter the row you are choosing from: ";
	cin >> row;
	cout << "Enter the column you are choosing from: ";
	cin >> column;
	while (moveIsValid(boardSize, row, column) == false)
	{
		cout << endl << "The number you have chosen is either too high or too low, choose again" << endl;
		cout << "Row: ";
		cin >> row;
		cout << endl << "Column: ";
		cin >> column;
	}

	cout << "You have chosen row " << row << " and column " << column << endl;
	cout << "Would you like to mark this location as a mine? (y/n)" << endl;
	cin >> choice;

	bool gameOver = false;

	switch (choice)
	{
	case 'y':
	case 'Y':
		board[row][column] = 'ele'; // put the flag in this location
		break;
	case 'n':
	case 'N':
		gameOver = examineLocation(row, column, boardSize, board);
		break;
	default:
		cout << "Would you like to mark this location as a mine? (y/n)" << endl
			<< "Enter 'y' or 'Y' for yes and 'n' or 'N' for no" << endl;
		cin >> choice;
		break;
	}
	return gameOver;
}
// Post-condition: Based on user's choice on row and column, it checks if the game is over, if yes then returns true, else it returns false

// Pre-condition: The boardSize, the current row, and the current column is passed in as arguments
bool MineSweeper::moveIsValid(int boardSize, int row, int column)
{
	return (row >= 0 && row < boardSize&& column >= 0 && column < boardSize);
}
// Post-condition: If move doesn't exceed board limits, returns true, else it returns false

// Pre-condition: The current row, the current column, and the board are passed in as arguments
bool MineSweeper::checkIfMine(int row, int column, char board[][MAX_SIZE])
{
	if (board[row][column] == 'n')
	{
		return true;
	}
	else
		return false;
}
// Post-condition: Checks to see if the move is a mine, if yes then returns true, else it returns false

// Pre-condition: The current row, the current column, the boardSize, and the board are sent in as arguments
int MineSweeper::countAdjacentMines(int row, int column, int boardSize, char board[][MAX_SIZE])
{
	int count = zero;

	// North
	if (moveIsValid(boardSize, row - one, column) == true)
	{
		if (checkIfMine(row - one, column, board) == true)
			count++;
	}

	// South
	if (moveIsValid(boardSize, row + one, column) == true)
	{
		if (checkIfMine(row + one, column, board) == true)
			count++;
	}

	// East
	if (moveIsValid(boardSize, row, column + one) == true)
	{
		if (checkIfMine(row, column + one, board) == true)
			count++;
	}

	// West
	if (moveIsValid(boardSize, row, column - one) == true)
	{
		if (checkIfMine(row, column - one, board) == true)
			count++;
	}

	// North-east
	if (moveIsValid(boardSize, row - one, column + one) == true)
	{
		if (checkIfMine(row - one, column + one, board) == true)
			count++;
	}

	// North-west
	if (moveIsValid(boardSize, row - one, column - one) == true)
	{
		if (checkIfMine(row - one, column - one, board) == true)
			count++;
	}

	// South-east
	if (moveIsValid(boardSize, row + one, column + one) == true)
	{
		if (checkIfMine(row + one, column + one, board) == true)
			count++;
	}

	// South-west
	if (moveIsValid(boardSize, row + one, column - one) == true)
	{
		if (checkIfMine(row + one, column - one, board) == true)
			count++;
	}

	return count;
}
// Post-condition: Goes all around the current location in the board to determine if there are any mines nearby, returns the number of spaces that the current location is adjacent to a mine

// Pre-condition: The current row, the current column, the boardSize, and the board are passed in as arguments
bool MineSweeper::examineLocation(int row, int column, int boardSize, char board[][MAX_SIZE])
{

	if (checkIfMine(row, column, board))
	{
		printf("\t");
		for (int i = 0; i < boardSize; i++)
		{
			printf("%2d ", i);
		}
		printf("\n\n");
		for (int i = zero; i < boardSize; i++)
		{
			printf("%d\t", i);
			for (int j = zero; j < boardSize; j++)
			{
				if (checkIfMine(i, j, board))
				{
					printf("%2c ", '*');
					continue;
				}
				int count = countAdjacentMines(i, j, boardSize, board);
				board[i][j] = count + '0';
				if (board[i][j] != 'n')
				{
					printf("%2c ", board[i][j]);
				}
			}
			printf("\n");
		}

		bool gO = gameOver();
		return gO;
	}
	else
	{
		int count = countAdjacentMines(row, column, boardSize, board);
		board[row][column] = count + '0';
	}
	return false;
}
// Post-condition: If the current location is a mine, then ends the game by returning true, if not then calls countAdjacentMines to figure out the count and returns false

bool MineSweeper::gameOver()
{
	cout << endl;
	int size = eleven;
	int radius = five;
	int dist;

	for (int i = zero; i < size; i++) {
		for (int j = zero; j < size; j++) {
			dist = sqrt(pow(i - radius, 2) + pow(j - radius, 2));
			if ((i == j || i + j == size - one) && dist <= radius) {
				cout << "*";
			}
			else if (dist < radius + 0.5) {
				cout << "|";
			}
			else {
				cout << " ";
			}
		}
		cout << "\t";

		for (int j = zero; j < size; j++) {
			dist = sqrt(pow(i - radius, 2) + pow(j - radius, 2));
			if ((i == j || i + j == size - one) && dist <= radius) {
				cout << "*";
			}
			else if (dist < radius + 0.5) {
				cout << "|";
			}
			else {
				cout << " ";
			}
		}
		cout << endl;
	}

	cout << "\n\n ---------------------------" << endl;
	cout << "                   \\   |   /" << endl;
	cout << "                    \\  |  /" << endl;
	cout << "                      ---" << endl;

	cerr << "Game over" << endl << "You hit a mine" << endl;
	bool gameOver = true;
	return gameOver;
}
// Post-condition: Returns true to indicate that the game is over and prints the game over message
