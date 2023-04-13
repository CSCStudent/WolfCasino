#include <iostream>
#include <string>
#include "Casino.h"


namespace CSC2034 {
	//class Casino implementation file
	void Casino::play(string gameName) {
		Casino* game = NULL;   //pointer can refer to object of subclass

		if (gameName == "TicTacToeGame")
			game = NULL; // TicTacToeGame::makeGame();

		else
			throw NoGame(gameName + " game not found!!");

		game->start();  // using late binding, invoke game start
		delete game;	// cleaning up heap

	}

	void Casino::start() {
		std::cout << "Subclass funtion start() is not defined." << endl;
	}

	Casino::~Casino() {
		std::cout << "Casino desctructor here" << endl;
	}
}
