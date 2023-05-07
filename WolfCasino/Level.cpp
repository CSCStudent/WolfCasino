/*
Copyright (c) 2023 Hridaya Bijayananda
Author: Hridaya Bijayananda
*/

#include "Level.h"

using namespace MS;

Level::Level()
{}

Level::~Level()
{}

int Level::chooseLevel()
{
	cout << "Enter 1, 2, or 3 to choose which level you would like to play" << endl;
	printf("\nLevel 1. Beginner: 9 * 9 board with 10 mines \n");
	printf("Level 2. Intermidiate: 16 * 16 board with 40 mines \n");
	printf("Level 3. Advanced: 25 * 25 board with 99 mines \n");
	
	int choice;
	cout << endl << "Level: ";
	cin >> choice;
	
	int size = adjustLevelSettings(choice);
	return size;
}

int Level::adjustLevelSettings(int choice) 
{
	Board board;
	switch (choice)
	{
	case one:
		board.boardSize = 9;
		break;

	case two:
		board.boardSize = 16;
		break;

	case three:
		board.boardSize = 25;
		break;
	default: // default is the beginner level
		board.boardSize = 9;
		break;
	}
	
	return board.boardSize;
}