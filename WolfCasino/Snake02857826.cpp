#include "Snake02857826.h"
namespace CSC2034 {
	void Snake02857826::up() {
		cycleSnakeArray();
		int temp = snake.front().front() - 1;
		snake.front().front() = temp;
	}
	void Snake02857826::left() {
		cycleSnakeArray();
		int temp = snake.front().back() - 1;
		snake.front().back() = temp;
	}
	void Snake02857826::down() {
		cycleSnakeArray();
		int temp = snake.front().front() + 1;
		snake.front().front() = temp;
	}
	void Snake02857826::right() {
		cycleSnakeArray();
		int temp = snake.front().back() + 1;
		snake.front().back() = temp;
	}
	//Debugging function
	void Snake02857826::printSnake() {
		for (int i = 0; i < snake.size(); i++) {
			std::cout << "pos " << i << ": y" << snake[i].front() << " x" << snake[i].back() << " | ";
		}
		std::cout << "\n";
	}
	void Snake02857826::cycleSnakeArray() {
		int end = snake.size() - 1;
		if (snake.size() > 1) {
			for (int i = end; i > 0; i--) {
				std::vector<int> temp = snake[i - 1];
				snake[i] = temp;
				//int tempy = snake[i - 1].front();
				//int tempx = snake[i - 1].back();
				//snake[i].front() = tempy;
				//snake[i].back() = tempx;
			}
		}
	}
	void Snake02857826::addSegment() {
		snake.push_back(std::vector<int>{START_Y, START_X});
	}
	void Snake02857826::addSegment(std::vector<int> newPos) {
			if (snake.empty()) {
				snake.push_back(std::vector<int>{START_Y, START_X});
			}
			else {
				if (snake.size() > 1) {
					snake.push_back(newPos);
					//int tempy = snake.back().front();
					//int tempx = snake.back().back();
					//snake.push_back(std::vector<int>(tempy, tempx));
				}
				else {
					snake.push_back(newPos);
					//int tempy = snake.front().front();
					//int tempx = snake.front().back();
					//snake.push_back(std::vector<int>(tempy, tempx));
				}

			}
	}
	std::vector<int> Snake02857826::getFront() {
		return snake.front();
	}
	std::vector<int> Snake02857826::getBack() {
		if (snake.size() > 1) {
			return snake.back();
		}
		else {
			return snake.front();
		}
	}
	int Snake02857826::getSize() {
		return snake.size();
	}
}
