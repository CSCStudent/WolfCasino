#include <iostream>
#include "Checkers.h"

namespace S02257117 {
	checkers::checkers() {};

	checkers* checkers::makeGame() {
		return new checkers;
	}

	//This plays the game
	void checkers::start() {
		run();
	}

	void checkers::run() {
		CheckersPlayer player1; player1.setPNumber(1);          // creates player 1 and sets their player number to 1
		player1.setPScore(0);							// sets player1 player score to 0 to zero out the pscore.
		CheckersPlayer player2; player2.setPNumber(2);			// Creates player 2 and sets their player number to 2
		player2.setPScore(0);							// Sets player 2 player score to 0 to zero out the pscore
		int winner = 0;									// makes sure the winner is set to 0.

		fillBoard();								// fills the array with the tiles setting up the game. 

		printBoard();								// displays the board to the console.
		while (!player1.getWin() || !player2.getWin()) // the loop for the game play. 
		{
			if (player2.getPScore() < 12)              // check to make sure that player2 has not won before the final check
			{
				player1.setPScore(move(player1)); // calls the move function  which is passed the current player and the board returns the player score
			}
			if (player1.getPScore() < 12)               // checks to make sure player1 has not won the game, by default player 2 will be called to move even if they have lost.
			{
				player2.setPScore(move(player2));
			}

			std::cout << std::endl << "Player" << player1.getPNumber() << " score: " << player1.getPScore() << std::endl;	// outputs player 1 score
			std::cout << "Player" << player2.getPNumber() << " score: " << player2.getPScore() << std::endl;				// outputs player 2 score
			if (player1.getPScore() == 12)							//checks if player1 has won the game
			{
				player1.setWin(true);								// sets player1.win() to true
				winner = player1.getPNumber();                      // sets winner to 1 to declare player 1 as winner
			}
			else if (player2.getPScore() == 12)						// checks if player2 has won the game
			{
				player2.setWin(true);								// sets player2.win() to true.
				winner = player2.getPNumber();						// sets winner to 2 to declare player 2 as winner
			}
		}
		std::cout << "Player " << winner << "is the winner. " << std::endl	// prints out the winner. 
			<< "player 1 score: " << player1.getPScore() << "  player 2 score: " << player2.getPScore(); //prints out the final score

		std::cout << std::endl;
		return;

	}

	// the function used to neatly display the board to the console.
	void checkers::printBoard() {
		int j = 1; // sets coordinate iterator for the display to 1 to create more friendly coordinates. 
		int l = 1;
		for (int i = 0; i < 8; i++) // outer loop for the 2D array
		{

			if (j != 1)  // checks to see if the first row has been printed. Then proceeds to print the y-axis numbers at the start of every row
			{
				l = i + 1;
				printf("%d", l);
			}
			for (int k = 0; k < 8; k++)// inner loop for the 2D array
			{
				for (j; j < 9; j++) // prints the x-axis coordinate numbers
				{

					printf("%*d ", 4, j);

				}
				if (j == 9) // after the x-axis coordinate numbers have been created this prints the first number for the y-axis then makes sure j is greater than 9
				{
					std::cout << std::endl; printf("%d", l);
					j++;
				}

				std::cout << "| " << board[i][k].getTile() << "  ";  // Creates the boxes and displays what is currently in each location in the array.

			}
			std::cout << "|" << std::endl;// closes the last box then drops to the next line 
			std::cout << "  ";
			for (int i = 0; i < 40; i++) // prints out a line under every "square" to make the squares. 
			{

				printf("%c", '-');
			}
			printf("\n");
		}
		return;
	}

	// fills the board with the starting pieces for both players. 
	void checkers::fillBoard() {
		for (int i = 0; i < 8; i++)   // outer loop for iterating through the 2D array
		{
			for (int k = 0; k < 8; k++) // inner loop for iterating through the 2D array
			{
				if (i == 0 && k % 2 != 0) //places a '*' tile for player one on every other tile in the first row
				{
					pawn pawn;
					pawn.setx(k);
					pawn.sety(i);
					pawn.setTile('*');
					board[i][k].setTile(pawn.getTile());
				}
				else if (i == 1 && k % 2 == 0) // places a '*' tile on the second row on every other tile in the 
				{
					pawn pawn;
					pawn.setx(k);
					pawn.sety(i);
					pawn.setTile('*');
					board[i][k].setTile(pawn.getTile());

				}
				else if (i == 2 && k % 2 != 0) // places a '*' tile on every other tile of the third row.
				{
					pawn pawn;
					pawn.setx(k);
					pawn.sety(i);
					pawn.setTile('*');
					board[i][k].setTile(pawn.getTile());
				}
				else if (i == 5 && k % 2 == 0)  // places'^' for player 2 on every other tile of the fifth row
				{
					pawn pawn;
					pawn.setx(k);
					pawn.sety(i);
					pawn.setTile('^');
					board[i][k].setTile(pawn.getTile());
				}
				else if (i == 6 && k % 2 != 0)   // places '^' on every other tile on the sixth row
				{
					pawn pawn;
					pawn.setx(k);
					pawn.sety(i);
					pawn.setTile('^');
					board[i][k].setTile(pawn.getTile());
				}
				else if (i == 7 && k % 2 == 0) // places a '^' on every other tile on the seventh row
				{
					pawn pawn;
					pawn.setx(k);
					pawn.sety(i);
					pawn.setTile('^');
					board[i][k].setTile(pawn.getTile());
				}
				else {
					board[i][k].setTile(' '); // places ' ' on every other tile to make sure they are set as blank spaces.
				}
			}
		}
		return;
	}

	// The function for the players to move their pieces and capture pieces. returns playerscore
	int checkers::move(CheckersPlayer player) {
		int pXTChoice = 0;
		int pYTChoice = 0;
		// x y coordinates of a open square where a player wishes to move their selected tile. 
		int pXDChoice = -1;
		int pYDChoice = -1;
		int captureDif = 0;// used to calculate if the player has taken a piece.
		player.setPScore(0); // zeros out the player score.
		// gets the player coordinates for which piece they want to move.
		std::cout << "Player" << player.getPNumber() << " Pick an x coordinate and then a y coordinate to select which tile to move";
		std::cin >> pXTChoice; std::cin >> pYTChoice;

		pXTChoice = pXTChoice - 1; pYTChoice = pYTChoice - 1; // adjusts the input to work with the array,
		if (player.getPNumber() == 1)  // movement for player one check.
		{
			while (moveCheckF(pXTChoice, pYTChoice, pXDChoice, pYDChoice, player))  // loops to check the player choice to make sure it is legal.
			{
				std::cout << " please select a valid choice for player1 a ( * ) tile" << std::endl;
				std::cin >> pXTChoice; std::cin >> pYTChoice;
				pXTChoice = pXTChoice - 1; pYTChoice = pYTChoice - 1;

			}
			printf("\n%s\n", "Select a x and y destination for your tile. ");
			std::cin >> pXDChoice; std::cin >> pYDChoice;
			pXDChoice = pXDChoice - 1; pYDChoice = pYDChoice - 1;
			while (moveCheckF(pXTChoice, pYTChoice, pXDChoice, pYDChoice, player))  // loops again for the destination. 
			{
				std::cout << "Please pick a valid destination" << std::endl;
				std::cin >> pXDChoice; std::cin >> pYDChoice;
				pXDChoice = pXDChoice - 1; pYDChoice = pYDChoice - 1;

			}
			board[pYDChoice][pXDChoice].setTile('*'); //sets the destination tile as the new piece
			board[pYTChoice][pXTChoice].setTile(' '); // sets the old tile to be blank.
			captureDif = pYDChoice - pYTChoice;
			if (abs(captureDif) == 2)            // the check for if the player has captured a piece. gets the difference from pyDChoice and pYTChoice and takes the absolute value.
			{
				if (board[pYDChoice - 1][pXDChoice - 1].getTile() == '^') // checks for diagonal left for player 1 capture. 
				{
					board[pYDChoice - 1][pXDChoice - 1].setTile(' ');
					player.setPScore(1);
				}
				else if (board[pYDChoice - 1][pXDChoice + 1].getTile() == '^') // checks for diagonal right for player 1 capture.
				{
					board[pYDChoice - 1][pXDChoice + 1].setTile(' ');
					player.setPScore(1);
				}
				std::cout << std::endl << "Player" << player.getPNumber() << " captured a piece" << std::endl;

			}
			if (abs(captureDif) == 4)  // the check for player 1 double jump.
			{
				if (board[pYDChoice - 1][pXDChoice - 1].getTile() == '^' && board[pYDChoice - 3][pXDChoice - 3].getTile() == '^')
				{
					board[pYDChoice - 1][pXDChoice - 1].setTile(' ');
					player.setPScore(1);
					board[pYDChoice - 3][pXDChoice - 3].setTile(' ');
					player.setPScore(1);
				}
				if (board[pYDChoice - 1][pXDChoice + 1].getTile() == '^' && board[pYDChoice - 3][pXDChoice + 3].getTile() == '^')
				{
					board[pYDChoice - 1][pXDChoice + 1].setTile(' ');
					player.setPScore(1);
					board[pYDChoice - 3][pXDChoice + 3].setTile(' ');
					player.setPScore(1);
				}
				std::cout << std::endl << "Player" << player.getPNumber() << " captured a piece, Double jump!" << std::endl;

			}
		}
		else if (player.getPNumber() == 2) // move/capture for player 2 
		{
			while (moveCheckF(pXTChoice, pYTChoice, pXDChoice, pYDChoice, player)) // move check for player 2 piece selection.
			{
				std::cout << " please select a valid choice for player2  a ( ^ ) tile" << std::endl;
				std::cin >> pXTChoice; std::cin >> pYTChoice;
				pXTChoice = pXTChoice - 1; pYTChoice = pYTChoice - 1;
			}
			printf("\n%s\n", "Select a x and y destination for your tile. ");
			std::cin >> pXDChoice; std::cin >> pYDChoice;
			pXDChoice = pXDChoice - 1; pYDChoice = pYDChoice - 1;
			while (moveCheckF(pXTChoice, pYTChoice, pXDChoice, pYDChoice, player)) // move check for player 2 piece destination.
			{
				std::cout << "Please pick a valid destination" << std::endl;
				std::cin >> pXDChoice; std::cin >> pYDChoice;
				pXDChoice = pXDChoice - 1; pYDChoice = pYDChoice - 1;

			}
			board[pYDChoice][pXDChoice].setTile('^');
			board[pYTChoice][pXTChoice].setTile(' ');
			captureDif = pYDChoice - pYTChoice;

			if (abs(captureDif) == 2)   // the capture check for player 2.
			{
				if (board[pYDChoice + 1][pXDChoice + 1].getTile() == '*') // right diagonal capture check for player2.

				{
					board[pYDChoice + 1][pXDChoice + 1].setTile(' ');
					player.setPScore(1);
				}
				else if (board[pYDChoice + 1][pXDChoice - 1].getTile() == '*') // left diagonal capture check for player2.
				{
					board[pYDChoice + 1][pXDChoice - 1].setTile(' ');
					player.setPScore(1);
				}
				std::cout << std::endl << "Player" << player.getPNumber() << " captured a piece" << std::endl;

			}
			if (abs(captureDif) == 4) // double jump check for player 2.
			{
				if (board[pYDChoice + 1][pXDChoice + 1].getTile() == '*' && board[pYDChoice + 3][pXDChoice + 3].getTile() == '*')
				{
					board[pYDChoice + 1][pXDChoice + 1].setTile(' ');
					player.setPScore(1);
					board[pYDChoice + 3][pXDChoice + 3].setTile(' ');
					player.setPScore(1);
				}
				if (board[pYDChoice + 1][pXDChoice - 1].getTile() == '*' && board[pYDChoice + 3][pXDChoice - 3].getTile() == '*')
				{
					board[pYDChoice + 1][pXDChoice - 1].setTile(' ');
					player.setPScore(1);
					board[pYDChoice + 3][pXDChoice - 3].setTile(' ');
					player.setPScore(1);
				}
				std::cout << std::endl << "Player" << player.getPNumber() << " captured a piece, Double jump!" << std::endl;

			}

		}
		printBoard(); // prints the board after the player moves 
		return player.getPScore();   // returns the player score. 

	}

	bool checkers::moveCheckF(int xI, int yI, int xF, int yF, CheckersPlayer player) {
		int cCount = 0;
		if (board[yI][xI].getTile() != '*' && player.getPNumber() == 1)  // checks if player 1 is actually selecting their tile
			return true;
		if (board[yI][xI].getTile() != '^' && player.getPNumber() == 2)// checks if player 2 is actually selecting their tile
			return true;


		if (abs(yI - yF) > 2 && abs(yI - yF) < 4 && yF != -1) // checks if they are making a valid move IE moving more than 2 tiles at a time 
		{
			return true;
		}
		else if (abs(yI - yF) == 4 && yF != -1) // catch for the double jump. 
		{
			return false;
		}

		if (abs(xI - xF) > 2 && xF != -1)// checks if they are moving more than two tiles on the x-axis
			return true;
		if (player.getPNumber() == 1 && board[yF][xF].getTile() != ' ' && yF != -1) // checks if the player has selected a tile that is not empty !(' ')
			return true;
		if (player.getPNumber() == 2 && board[yF][xF].getTile() != ' ' && yF != -1)// checks if the player has selected a tile that is not empty !(' ') might be redundant. 
			return true;
		if (xI == xF) // checks if the player has tried to move in the same row "Horizontally"
			return true;

		if (yI == yF)   // checks if the player tried to move in the same column " vertically". 
			return true;
		for (int i = 0; i < 8; i++)// counts to see the row Infront of the tile selected actually has an open spot ad dose not have all '*' tiles or '^' for each players.
		{

			if (board[yI + 1][i].getTile() == '*' && player.getPNumber() == 1)
			{
				cCount++;
			}
			if (board[yI - 1][i].getTile() == '^' && player.getPNumber() == 2)
			{
				cCount++;
			}
		}
		if (!board[yI][xI].getKing() && player.getPNumber() == 1) // checks if the piece is a not a king and trying to move back for p1 
		{
			if (yI > yF && yF > -1)
			{
				return true;
			}
		}
		if (!board[yI][xI].getKing() && player.getPNumber() == 2)// checks if the piece is a not a king and trying to move back for p1 and p2.
		{
			if (yF > yI && yF > -1)
			{
				return true;
			}
		}

		if (cCount == 4 && (yI < 2 || yI >5))// returns true if the player has selected a tile that is behind their starting line.
			return true;

		return false; // returns false if the player has not made an illegal move.

	}

}