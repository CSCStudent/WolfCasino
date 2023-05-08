/*
Copyright (c) 2023 Hridaya Bijayananda
Author: Hridaya Bijayananda
*/

#ifndef Level_H
#define Level_H

#include <iostream>
#include "MineSweeper.h"
#include "Board.h"
#include "Mine.h"

using namespace std;
//using namespace MS;

namespace MS
{
	class Level
	{
	private:
		int adjustLevelSettings(int);
	public:
		int chooseLevel();
		Level();
		~Level();
	};
}

#endif // !Level_H