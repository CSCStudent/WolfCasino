#pragma once
#include <ctime>
#include <vector>
#include "Casino.h"

namespace CSC2034 {
	class HangMan : public Casino {

	public:

		HangMan();

		void start();
		static HangMan* makeGame();

	private:

		void run();
		const int MAXGUESS = 6;

		vector<char> guesses;

		int totalLosses = 0;
		int totalWins = 0;
		int totalPlayed = 0;

		int gameStart();
		bool validSelection(int difficulty);
		bool keepPlaying(int player);

		int guessLetter(string word, string& guessState, int& guessCount, int difficulty);
		string checkGuess(const string& word, const vector<char>& guesses);
		string getWord(ifstream& file);
		ifstream gameMode(bool selection, int difficulty);

		void gameOutcome(int guessCount, const string& word, const string& guessedWord);
		void printGameStart();
		void printLength(string& word);

		friend std::ostream& operator<<(std::ostream& oStream, const HangMan& hangMan);
	};
}

