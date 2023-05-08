// Carter Lyle
// CSC2034
// 5/07/2023

// Yahtzee
// CSC2034 Spring 2023
// Wolf Casino

#pragma once
#include <iostream>
#include <algorithm>
#include <string>

namespace CSC2034
{
	class Player
	{
	private:
		int playerNum;
			
			// If the score is -1, it is free to be used, if it is 0 or positive, it has already been used
			// Upper Section of Score Card
		int aces = -1;  // Total of all ones
		int twos = -1; 
		int threes = -1; 
		int fours = -1;
		int fives = -1;
		int sixes = -1; // Total of all sixes
		int upperScore = 0; // Total of aces to sixes
		int upperBonus = 0; // 35 if upperScore >= 63
		int upperTotal = 0; // upperScore + upperBonus
			
			// Lower Section of Score Card
		int threeOfAKind = -1;  // Total of all dice
		int fourOfAKind = -1;	// Total of all dice
		int fullHouse = -1;     // 0 or 25
		int smallStraight = -1; // 0 or 30
		int largeStraight = -1; // 0 or 40
		int yahtzee = -1;       // 0 or 50
		int chance = -1; // Total of all five dice
		int yahtzeeBonus = 0; // if 50 points in yahtzee, add 100 for each additional yahtzee
		int lowerTotal = 0;
			
			// total score for the player
		int grandTotal = 0; // upperTotal + lowerTotal


	public:
		Player( );
		Player(int, int);
		Player( int );
		// Precondition:  None
		// Postcondition: A Player with a number has been created
		// Creates a Player with a player number

		~Player( );

		int getPlayerNum( );
		// Returns playerNum

		int getGrandTotal( );
		// Returns grandTotal

		void addScore( int, int, int, int, int ); //ints are the dice
		// Precondition:  5 dice
		// Postcondition: a score is added to the scoreboard, and the current totals have been updated
		// Adds a score to a player's scoreboard fater asking input and checking for a their choice
		
		
		friend std::ostream& operator << ( std::ostream&, Player* );
		// Precondition:  a Player
		// Postcondition: prints Scoreboard of the player
		// Prints the scoreboard of the player
	};
}