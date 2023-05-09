#include "CheckersPlayer.h"

namespace S02257117 {
	CheckersPlayer::CheckersPlayer()
	{
		int pNumber = 0; // (player Number)
		int pScore = 0;  // (Player score)
		bool winner = false;
	}

	CheckersPlayer:: ~CheckersPlayer() {}

	// accessors
	int CheckersPlayer::getPNumber()
	{
		return pNumber;
	}
	int CheckersPlayer::getPScore()
	{
		return pScore;
	}
	bool CheckersPlayer::getWin()
	{
		return winner;
	}

	// mutators
	void CheckersPlayer::setPNumber(int pNumber)
	{
		this->pNumber = pNumber;
	}
	void CheckersPlayer::setPScore(int pScore)
	{
		this->pScore += pScore;
	}
	void CheckersPlayer::setWin(bool winner)
	{
		this->winner = winner;
	}
}
