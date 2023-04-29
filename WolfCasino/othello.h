#pragma once
#include <iostream>
#include <windows.h>
#include <conio.h>
#include "Casino.h"

//using namespace std;

namespace CSC2034 {
	class othello : public Casino {
	private:
		int gameBoard[8][8] = {0,0,0,0,0,0,0,0,
								0,0,0,0,0,0,0,0,
								0,0,0,0,0,0,0,0,
								0,0,0,1,2,0,0,0,
								0,0,0,2,1,0,0,0,
								0,0,0,0,0,0,0,0,
								0,0,0,0,0,0,0,0,
								0,0,0,0,0,0,0,0 };

		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		int blackScore = 0;
		int whiteScore = 0;
	public:

		static othello* makeGame();
		void start();


		othello();
		~othello();
		bool placeToken(int arr[3]);
		void print();
		void updateScore();
		int getScore(int player);
		bool checkBoard();
		friend ostream& operator << (ostream&, othello&);
		void run();
	};
}