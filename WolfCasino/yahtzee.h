// Carter Lyle
// CSC2034
// 5/07/2023

// Yahtzee
// CSC2034 Spring 2023
// Wolf Casino

#pragma once

#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <string>

#include "Casino.h"
#include "player.h"


namespace CSC2034
{
	class Yahtzee : public Casino
	{
	private:
		int dice1;
		int dice2;
		int dice3;
		int dice4;
		int dice5;
		std::vector<Player*> players;


		Yahtzee( );
	
		~Yahtzee( );

		void play( );
		// Precondition:  None
		// Postcondition: Game is Over
		// Recieves input for number of players, calls createPlayers, calls playerRound to handle each turn, displays final scores

		void playerTurn( Player* );
		// Precondition:  a Player
		// Postcondition: The player's turn is over and scores have been added to their score card
		// Rolls dice and allows the Player to choose to reroll some dice or to score the dice

		void roll( int &dice );
		// Precondition:  None
		// Postcondition: dice has a new random number
		// assigns a new random number to the dice

		void createPlayers( int );
		// Precondition:  Number of Players in the game
		// Postcondition: Players have been created and added to players vector
		// Creates players and adds them to a vector, players

		void printDice( );
		// Precondition:  None
		// Postcondition: prints all dice
		// Prints dice to console


	public:
		static Yahtzee* makeGame( );
		// Precondition:  None
		// Postcondition: Creates an instance of Yahtzee

		void start( );
		// Precondition:  None
		// Calls Play
	};
}