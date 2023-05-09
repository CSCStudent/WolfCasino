#include "CheckersPawn.h"

namespace S02257117 {
	pawn::pawn()
	{
		int x = 0;
		int y = 0;
		bool king = false;
		char tile = ' ';
	}
	pawn :: ~pawn() {}
	// accessors
	int pawn::getx()
	{
		return x;
	}
	int pawn::gety()
	{
		return y;
	}
	bool pawn::getKing()
	{
		return king;
	}
	char pawn::getTile()
	{
		return tile;
	}
	//mutators

	void pawn::setx(int x)
	{
		this->x = x;
	}
	void pawn::sety(int y)
	{
		this->y = y;
	}
	void pawn::setKing(bool king)
	{
		this->king = king;
	}
	void pawn::setTile(char tile)
	{
		this->tile = tile;
	}
}