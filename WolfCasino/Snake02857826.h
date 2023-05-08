#pragma once
#include <vector>
#include <iostream>

namespace CSC2034 {
	class Snake02857826 {
	private:
		std::vector<std::vector<int>> snake;
		void cycleSnakeArray();
		const int START_Y = 7;
		const int START_X = 15;
	public:
		void right();
		void left();
		void up();
		void down();
		void addSegment();
		void addSegment(std::vector<int>);
		int getSize();

		//Debugging function
		void printSnake();

		std::vector<int> getFront();
		std::vector<int> getBack();
	};
}


