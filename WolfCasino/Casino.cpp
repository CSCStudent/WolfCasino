#include <iostream>
#include <string>
#include "Casino.h"
#include "TicTacToe.h"
#include "othello.h"
#include "Blackjack.h"
#include "TicLogic.h"
#include "cardGame.h"
#include "Snake02857826.h"
#include "Roulette.h"
#include "Wordle.h"

// class Casino implemetation file
namespace CSC2034 {
	void Casino::play(string gameName) {
		Casino* game = NULL;   //pointer should refer to object of subclass

		if (gameName == "TicTacToe")
			game = TicTacToeGame::makeGame(); // TicTacToeGame::makeGame();

		else if (gameName == "Roulette")
			game = Roulette::makeGame();

		else if (gameName == "Wordle")
			game = wordle::makeGame();

		else if (gameName == "Othello")
			game = othello::makeGame();

    		else if (gameName == "Blackjack")
			game = Blackjack::makeGame();

		else if (gameName == "TicTacToeGame")
			game = TicLogic::makeGame();

		else if (gameName == "CardGame")
			game = CardGame::makeGame();

		else if (gameName == "Snake02857826")
			game = Snake02857826::makeGame();

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
