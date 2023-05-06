#include "Snake02857826.h"
namespace CSC2034 {
	Snake02857826::Snake02857826() {
		populateBoardArray(&snakeBoard);
		snake.push_back(Segment02857826(START_Y, START_X));
		snake.push_back(Segment02857826(START_Y, START_X - 1));
		snakeBoard[snake.front().getLocY()][snake.front().getLocX()] = '@';
		snakeBoard[snake.back().getLocY()][snake.back().getLocX()] = '@';
		addFood();
	}
	Snake02857826::~Snake02857826() {

	}
	Snake02857826* Snake02857826::makeGame() {
		return new Snake02857826;
	}
	void Snake02857826::start() {
		play();
	}
	void Snake02857826::play() {
		bool gameOver = false;
		char lastInput = 'd';
		char input = 'd';
		do {
			switch (input) {
			case 'w':
				do {
					if (snakeBoard[snake.front().getLocY() - 1][snake.front().getLocX()] == '@') {
						gameOver = true;
						break;
					}
					if (snakeBoard[snake.front().getLocY() - 1][snake.front().getLocX()] == 'O') {
						addSegment();
						addFood();
						score++;
						Sleep(BASE_SPEED - speed());
						gameOver = up();
						system("cls");
						printBoard(&snakeBoard);
						input = direction();
						if (input == 'a' || input == 'd') {
							lastInput = 'w';
							break;
						}
					}
					else {
						Sleep(BASE_SPEED - speed());
						gameOver = up();
						system("cls");
						printBoard(&snakeBoard);
						input = direction();
						if (input == 'a' || input == 'd') {
							lastInput = 'w';
							break;
						}
					}
				} while (!gameOver);
				break;
			case 'a':
				do {
					if (snakeBoard[snake.front().getLocY()][snake.front().getLocX() - 1] == '@') {
						gameOver = true;
						break;
					}
					if (snakeBoard[snake.front().getLocY()][snake.front().getLocX() - 1] == 'O') {
						addSegment();
						addFood();
						score++;
						Sleep(BASE_SPEED - speed());
						gameOver = left();
						system("cls");
						printBoard(&snakeBoard);
						input = direction();
						if (input == 'w' || input == 's') {
							lastInput = 'a';
							break;
						}
					}
					else {
						Sleep(BASE_SPEED - speed());
						gameOver = left();
						system("cls");
						printBoard(&snakeBoard);
						input = direction();
						if (input == 'w' || input == 's') {
							lastInput = 'a';
							break;
						}
					}

				} while (!gameOver);
				break;
			case 's':
				do {
					if (snakeBoard[snake.front().getLocY() + 1][snake.front().getLocX()] == '@') {
						gameOver = true;
						break;
					}
					if (snakeBoard[snake.front().getLocY() + 1][snake.front().getLocX()] == 'O') {
						addSegment();
						addFood();
						score++;
						Sleep(BASE_SPEED - speed());
						gameOver = down();
						system("cls");
						printBoard(&snakeBoard);
						input = direction();
						if (input == 'a' || input == 'd') {
							lastInput = 's';
							break;
						}
					}
					else {
						Sleep(BASE_SPEED - speed());
						gameOver = down();
						system("cls");
						printBoard(&snakeBoard);
						input = direction();
						if (input == 'a' || input == 'd') {
							lastInput = 's';
							break;
						}
					}
				} while (!gameOver);
				break;
			case 'd':
				do {
					if (snakeBoard[snake.front().getLocY()][snake.front().getLocX() + 1] == '@') {
						gameOver = true;
						break;
					}
					if (snakeBoard[snake.front().getLocY()][snake.front().getLocX() + 1] == 'O') {
						addSegment();
						addFood();
						score++;
						Sleep(BASE_SPEED - speed());
						gameOver = right();
						system("cls");
						printBoard(&snakeBoard);
						input = direction();
						if (input == 'w' || input == 's') {
							lastInput = 'd';
							break;
						}
					}
					else {
						Sleep(BASE_SPEED - speed());
						gameOver = right();
						system("cls");
						printBoard(&snakeBoard);
						input = direction();
						if (input == 'w' || input == 's') {
							lastInput = 'd';
							break;
						}
					}

				} while (!gameOver);
				break;
			}
		} while (!gameOver);
		std::printf("Game over!\nYour score was: %i\n", score);
	}
	int Snake02857826::speed() {
		if (score * SPEED_MULT < BASE_SPEED) {
			return score * SPEED_MULT;
		}
		else {
			return BASE_SPEED;
		}
	}
	char Snake02857826::direction() {
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
	}
	void Snake02857826::addFood() {
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

	void Snake02857826::addSegment() {
		snake.push_back(Segment02857826(snake.back().getLocY(), snake.back().getLocX()));
		snakeBoard[snake.back().getLocY()][snake.back().getLocX()];

	}

	bool Snake02857826::up() {
		if (snake.front().getLocY() - 1 >= 0) {
			int end = snake.size() - 1;
			int tempx = snake.back().getLocX();
			int tempy = snake.back().getLocY();

			if (snake.back().getLocY() == snake[end - 1].getLocY()
				&& snake.back().getLocX() == snake[end - 1].getLocX()) {
				cycleSnakeArray();
				snake.front().setLocY(snake.front().getLocY() - 1);
				snakeBoard[snake.front().getLocY()][snake.front().getLocX()] = '@';
			}
			else {
				cycleSnakeArray();
				snake.front().setLocY(snake.front().getLocY() - 1);
				snakeBoard[snake.front().getLocY()][snake.front().getLocX()] = '@';
				snakeBoard[tempy][tempx] = ' ';
			}

			return false;
		}
		else {
			return true;
		}

	}
	bool Snake02857826::left() {
		if (snake.front().getLocX() - 1 >= 0) {
			int end = snake.size() - 1;
			int tempx = snake.back().getLocX();
			int tempy = snake.back().getLocY();

			if (snake.back().getLocY() == snake[end - 1].getLocY()
				&& snake.back().getLocX() == snake[end - 1].getLocX()) {
				cycleSnakeArray();
				snake.front().setLocX(snake.front().getLocX() - 1);
				snakeBoard[snake.front().getLocY()][snake.front().getLocX()] = '@';
			}
			else {
				cycleSnakeArray();
				snake.front().setLocX(snake.front().getLocX() - 1);
				snakeBoard[snake.front().getLocY()][snake.front().getLocX()] = '@';
				snakeBoard[tempy][tempx] = ' ';
			}
			return false;
		}
		else {
			return true;
		}
	}
	bool Snake02857826::down() {
		if (snake.front().getLocY() + 1 < 15) {
			int end = snake.size() - 1;
			int tempx = snake.back().getLocX();
			int tempy = snake.back().getLocY();

			if (snake.back().getLocY() == snake[end - 1].getLocY()
				&& snake.back().getLocX() == snake[end - 1].getLocX()) {
				cycleSnakeArray();
				snake.front().setLocY(snake.front().getLocY() + 1);
				snakeBoard[snake.front().getLocY()][snake.front().getLocX()] = '@';
			}
			else {
				cycleSnakeArray();
				snake.front().setLocY(snake.front().getLocY() + 1);
				snakeBoard[snake.front().getLocY()][snake.front().getLocX()] = '@';
				snakeBoard[tempy][tempx] = ' ';
			}
			return false;
		}
		else {
			return true;
		}
	}
	bool Snake02857826::right() {
		if (snake.front().getLocX() + 1 < 30) {
			int end = snake.size() - 1;
			int tempx = snake.back().getLocX();
			int tempy = snake.back().getLocY();

			if (snake.back().getLocY() == snake[end - 1].getLocY()
				&& snake.back().getLocX() == snake[end - 1].getLocX()) {
				cycleSnakeArray();
				snake.front().setLocX(snake.front().getLocX() + 1);
				snakeBoard[snake.front().getLocY()][snake.front().getLocX()] = '@';
			}
			else {
				cycleSnakeArray();
				snake.front().setLocX(snake.front().getLocX() + 1);
				snakeBoard[snake.front().getLocY()][snake.front().getLocX()] = '@';
				snakeBoard[tempy][tempx] = ' ';
			}
			return false;
		}
		else {
			return true;
		}
	}
	void Snake02857826::cycleSnakeArray() {
		int end = snake.size() - 1;
		for (int i = end; i > 0; i--) {
			snake[i].setLocY(snake[i - 1].getLocY());
			snake[i].setLocX(snake[i - 1].getLocX());
		}
	}

	void Snake02857826::populateBoardArray(char(*snakeBoard)[BOARD_HEIGHT][BOARD_WIDTH]) {
		for (int i = 0; i < BOARD_HEIGHT; i++) {

			for (int j = 0; j < BOARD_WIDTH; j++) {
				(*snakeBoard)[i][j] = ' ';
			}
		}
	}
	void Snake02857826::printBoard(char(*snakeBoard)[BOARD_HEIGHT][BOARD_WIDTH]) {
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