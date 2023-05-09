#pragma once

namespace S02257117 {

	class pawn
	{
	private:
		int x = 0; // x coordinate
		int y = 0; // y coordinate
		bool king = false; // set true if the piece is a king
		char tile = ' '; // the tile  type (' ' '*' '^')
	public:
		pawn(); // constructor
		~pawn();// destructor
		// accessors
		int getx();  //gets the x-axis
		int gety();	// gets the y-axis
		char getTile();// gets the tile
		bool getKing();// gets the bool for if the piece is a king
		// mutators
		void setx(int x); // sets the value for the x-axis
		void sety(int y); // sets the value for the y-axis
		void setKing(bool king); //  sets the value for the king.
		void setTile(char tile); // sets the value for the tile.


	};
}
