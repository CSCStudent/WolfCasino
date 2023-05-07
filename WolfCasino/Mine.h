/*
Copyright (c) 2023 Hridaya Bijayananda
Author: Hridaya Bijayananda
*/

#ifndef Mine_H
#define Mine_H

#include <iostream>
#include "MineSweeper.h"

using namespace std;
//using namespace MS;

namespace MS
{
	class Mine
	{
	private:
		int mineNum;
	public:
		Mine();
		~Mine();
		void putMine(int[][two], char[][MAX_SIZE], int, int);
	};
}

#endif // !Mine_H