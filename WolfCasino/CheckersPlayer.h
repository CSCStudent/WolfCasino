#pragma once
#include "Casino.h"

namespace S02257117 {
	class CheckersPlayer : public CSC2034::Casino
	{
	private:
		int pNumber = 0; // the value for the player number( who is player 1 who is player 2).
		int pScore = 0; // the value for player score ( who is winning). 
		bool winner = false; // the truth value for if the player has won or not.

	public:
		CheckersPlayer(); // constructor
		~CheckersPlayer(); // destructor
		//accessors
		int getPNumber(); // gets the value for player number
		int getPScore();  // gets the value for the player score
		bool getWin();    // gets the truth value for the winner.
		// mutators
		void setPNumber(int pNumber); // sets the value for the player number
		void setPScore(int pScore);   // sets the value for the player score.
		void setWin(bool winner);     // sets the truth value for winner.

	};

}