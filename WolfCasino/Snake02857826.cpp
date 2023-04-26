#include "SnakeHeader02857826.h"

using namespace std;

void Snake02857826::run() {
	bool gameOver = false;
	populateBoardArray(&snakeBoard);
	//printBoard(&snakeBoard);
	snake.push_back(Segment02857826(START_Y, START_X));
	snake.push_back(Segment02857826(START_Y, START_X - 1));
	snakeBoard[snake.front().getLocY()][snake.front().getLocX()] = '@';
	snakeBoard[snake.back().getLocY()][snake.back().getLocX()] = '@';
	printBoard(&snakeBoard);

	do {
		printBoard(&snakeBoard);
		char input = tolower(_getch());
		gameOver = loss();
		switch (input) {
		case 'w':
			if (snakeBoard[snake.front().getLocY() - 1][snake.front().getLocX()] == '@') {
				gameOver = true;
				break;
			}
			else {
				up();
				break;
			}
		case 'a':
			if (snakeBoard[snake.front().getLocY()][snake.front().getLocX() - 1] == '@') {
				gameOver = true;
				break;
			}
			else {
				left();
				break;
			}
		case 's':
			if (snakeBoard[snake.front().getLocY() + 1][snake.front().getLocX()] == '@') {
				gameOver = true;
				break;
			}
			else {
				down();
				break;
			}
		case 'd':
			if (snakeBoard[snake.front().getLocY()][snake.front().getLocX() + 1] == '@') {
				gameOver = true;
				break;
			}
			else {
				right();
			}
		}
		
	} while (!gameOver);
	//snake.~vector();
	cout << "Game over!";
}
void Snake02857826::up() {
	int tempx = snake.back().getLocX();
	int tempy = snake.back().getLocY();
	snake.back().setLocY(snake.front().getLocY());
	snake.back().setLocX(snake.front().getLocX());
	snake.front().setLocY(snake.front().getLocY() - 1);
	snakeBoard[snake.front().getLocY()][snake.front().getLocX()] = '@';
	snakeBoard[tempx][tempy] = ' ';
	
}
void Snake02857826::left() {
	int tempx = snake.back().getLocX();
	int tempy = snake.back().getLocY();
	snake.back().setLocY(snake.front().getLocY());
	snake.back().setLocX(snake.front().getLocX());
	snake.front().setLocX(snake.front().getLocX() - 1);
	snakeBoard[snake.front().getLocY()][snake.front().getLocX()] = '@';
	snakeBoard[tempx][tempy] = ' ';
}
void Snake02857826::down() {
	int tempx = snake.back().getLocX();
	int tempy = snake.back().getLocY();
	snake.back().setLocY(snake.front().getLocY());
	snake.back().setLocX(snake.front().getLocX());
	snake.front().setLocY(snake.front().getLocY() + 1);
	snakeBoard[snake.front().getLocY()][snake.front().getLocX()] = '@';
	//snakeBoard[snake.back().getLocY()][snake.back().getLocX()] = ' ';
	snakeBoard[tempx][tempy] = ' ';
}
void Snake02857826::right() {
	int tempx = snake.back().getLocX();
	int tempy = snake.back().getLocY();
	snake.back().setLocY(snake.front().getLocY());
	int temp1 = snake.back().getLocY();
	snake.back().setLocX(snake.front().getLocX());
	int temp2 = snake.back().getLocX();
	snake.front().setLocX(snake.front().getLocX() + 1);
	snakeBoard[snake.front().getLocY()][snake.front().getLocX()] = '@';
	snakeBoard[tempx][tempy] = ' ';
}
bool Snake02857826::loss() {
	if (snake.front().getLocX() > 30 || snake.front().getLocX() < 0
		|| snake.front().getLocY() > 15 || snake.front().getLocY() < 0) {
		return true;
	}
	else {
		/*for (vector<Segment02857826>::iterator itr = snake.begin(); itr < snake.end(); itr++) {
			int i = 1;
			if (snake.front().getLocX() == snake.at(i).getLocX() 
				&& snake.front().getLocY() == snake.at(i).getLocY()) {
				return true;
			}
			i++;
		}*/
		return false;
	}
	//return false;
}

void Snake02857826::populateBoardArray(char (*snakeBoard)[BOARD_HEIGHT][BOARD_WIDTH]) {
	for (int i = 0; i < BOARD_HEIGHT; i++) {
		
		for (int j = 0; j < BOARD_WIDTH; j++) {
			(*snakeBoard)[i][j] = ' ';
		}
	}
}
void Snake02857826::printBoard(char(*snakeBoard)[BOARD_HEIGHT][BOARD_WIDTH]) {
	cout << "+------------------------------+\n";
	for (int i = 0; i < BOARD_HEIGHT; i++) {
		cout << ".";
		for (int j = 0; j < BOARD_WIDTH; j++) {
			printf("%c", (*snakeBoard)[i][j]);
			
		}
		cout << ".\n";
	}
	cout << "+------------------------------+\n";
}
