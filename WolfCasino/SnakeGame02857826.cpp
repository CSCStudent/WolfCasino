#include "SnakeGame02857826.h"
namespace CSC2034 {
	SnakeGame02857826::SnakeGame02857826() {
		populateBoardArray(&snakeBoard);
		snake.addSegment();
		snakeBoard[snake.getFront().front()][snake.getFront().back()] = '@';
		addFood();
		printBoard(&snakeBoard);
	}
	SnakeGame02857826* SnakeGame02857826::makeGame() {
		return new SnakeGame02857826;
	}
	void SnakeGame02857826::start() {
		play();
	}
	void SnakeGame02857826::play()
	{
		bool gameOver = false;
		char lastInput = 'd';
		char input = 'd';
		do
		{
			if (!isGameOver(input))
			{
				Sleep(BASE_SPEED - speed());
				std::vector<int> temp = snake.getBack();
				switch (input)
				{
				case 'w':
					if (lastInput == 's' && snake.getSize() > 1) {
						snake.down();
					}
					else {
						snake.up();
						lastInput = 'w';
					}
					break;
				case 'a':
					if (lastInput == 'd' && snake.getSize() > 1) {
						snake.right();
					}
					else {
						snake.left();
						lastInput = 'a';
					}
					break;
				case 's':
					if (lastInput == 'w' && snake.getSize() > 1) {
						snake.up();
					}
					else {
						snake.down();
						lastInput = 's';
					}
					break;
				case 'd':
					if (lastInput == 'a' && snake.getSize() > 1) {
						snake.left();
					}
					else {
						snake.right();
						lastInput = 'd';
					}
					break;
				}
				bool test = false;
				if (snakeBoard[snake.getFront().front()][snake.getFront().back()] == 'O') {
					snake.addSegment(temp);
					test = true;
					addFood();
					score++;
				}
				if (temp != snake.getBack()) {
					snakeBoard[temp.front()][temp.back()] = ' ';
				}
				snakeBoard[snake.getFront().front()][snake.getFront().back()] = '@';
				system("cls");
				printBoard(&snakeBoard);
				//Below is a debugging tool
				//snake.printSnake();
			}
			else
			{
				gameOver = true;
			}
			input = direction(input);
		} while (!gameOver);
		std::printf("Game over!\nYour score was: %i\n", score);
	}
	bool SnakeGame02857826::isGameOver(char input) {
		//Switch to check if the snake will run into itself,
		//or into an edge.
		switch (input) {
		case 'w':
			if (snakeBoard[snake.getFront().front() - 1][snake.getFront().back()] == '@') {
				return true;
			}
			else if (snake.getFront().front() < 0) {
				return true;
			}
			else {
				return false;
			}
		case 'a':
			if (snakeBoard[snake.getFront().front()][snake.getFront().back() - 1] == '@') {
				return true;
			}
			else if (snake.getFront().back() < 0) {
				return true;
			}
			else {
				return false;
			}
		case 's':
			if (snakeBoard[snake.getFront().front() + 1][snake.getFront().back()] == '@') {
				return true;
			}
			else if (snake.getFront().front() >= 15) {
				return true;
			}
			else {
				return false;
			}
		case 'd':
			if (snakeBoard[snake.getFront().front()][snake.getFront().back() + 1] == '@') {
				return true;
			}
			else if (snake.getFront().back() >= 30) {
				return true;
			}
			else {
				return false;
			}
		}
	}
	bool SnakeGame02857826::foodDetected(char input) {
		switch (input) {
		case 'w':
			if (snakeBoard[snake.getFront().front() - 1][snake.getFront().back()] == 'O') {
				return true;
				break;
			}
		case 'a':
			if (snakeBoard[snake.getFront().front()][snake.getFront().back() - 1] == 'O') {
				return true;
				break;
			}
		case 's':
			if (snakeBoard[snake.getFront().front() + 1][snake.getFront().back()] == 'O') {
				return true;
				break;
			}
		case 'd':
			if (snakeBoard[snake.getFront().front()][snake.getFront().back() + 1] == 'O') {
				return true;
				break;
			}
		}
	}
	int SnakeGame02857826::speed() {
		if (score * SPEED_MULT < BASE_SPEED - 50) {
			return score * SPEED_MULT;
		}
		else {
			return BASE_SPEED - 50;
		}
	}
	char SnakeGame02857826::direction(char input) {
		if (GetAsyncKeyState(0x57)) {
			return 'w';
		}
		else if (GetAsyncKeyState(0x41)) {
			return 'a';
		}
		else if (GetAsyncKeyState(0x53)) {
			return 's';
		}
		else if (GetAsyncKeyState(0x44)) {
			return 'd';
		}
		return input;
	}
	void SnakeGame02857826::addFood() {
		srand(time(NULL));
		int randy = rand() % BOARD_HEIGHT;
		srand(time(NULL) - 100);
		int randx = rand() % BOARD_WIDTH;
		while (snakeBoard[randy][randx] == '@') {
			int i = 1;
			srand(time(NULL) + i);
			int randy = rand() % BOARD_HEIGHT;
			srand(time(NULL) - 100 + i);
			int randx = rand() % BOARD_WIDTH;
			i++;
		}
		snakeBoard[randy][randx] = 'O';

	}
	void SnakeGame02857826::populateBoardArray(char(*snakeBoard)[BOARD_HEIGHT][BOARD_WIDTH]) {
		for (int i = 0; i < BOARD_HEIGHT; i++) {

			for (int j = 0; j < BOARD_WIDTH; j++) {
				(*snakeBoard)[i][j] = ' ';
			}
		}
	}
	void SnakeGame02857826::printBoard(char(*snakeBoard)[BOARD_HEIGHT][BOARD_WIDTH]) {
		std::printf("Score: %i || Delay in ms : %i\n", score, BASE_SPEED - speed());
		std::cout << "+------------------------------+\n";
		for (int i = 0; i < BOARD_HEIGHT; i++) {
			std::cout << ".";
			for (int j = 0; j < BOARD_WIDTH; j++) {
				printf("%c", (*snakeBoard)[i][j]);
			}
			std::cout << ".\n";
		}
		std::cout << "+------------------------------+\n";
	}
}
