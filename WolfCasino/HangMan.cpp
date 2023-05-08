#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <random>
#include <ctype.h>
#include "HangMan.h"

using namespace std;

namespace CSC2034 {

	/*
	* Description:	Constructor
	* Pre-Condition:	no args
	*
	* Post-Condition:	data members initialized
	*/
	HangMan::HangMan() {
		this->totalLosses = 0;
		this->totalWins = 0;
		this->totalPlayed = 0;
	}

	/*
	* Description:	Creates a HangMan game object
	* Pre-Condition:	none
	*
	* Post-Condition:	points to a HangMan game object
	*/
	HangMan* HangMan::makeGame() {
		return new HangMan;
	}

	/*
	* Description:	Invokes game start
	* Pre-Condition:	HangMan game initialized
	*
	* Post-Condition:	run() is initialized
	*/
	void HangMan::start() {
		run();
	}

	/*
	* Description:	Runs the HangMan game
	* Pre-Condition:	Start() invoked and HangMan initalized ready for play
	*
	* Post-Condition:	The HangMan game is ran, user chooses how many rounds are played
	*/
	void HangMan::run() {
		int player = 1;
		keepPlaying(player);

		while (keepPlaying(player)) {
			totalPlayed++;
			int guessCount = 0;
			string guessState = "";
			guesses.clear();

			int difficulty = gameStart();
			bool selection = validSelection(difficulty);
			ifstream file = gameMode(selection, difficulty);
			string word = getWord(file);

			printLength(word);
			guessLetter(word, guessState, guessCount, difficulty);

			cout << "Would you like to play another game? Enter a '0' or '1' to play again, or enter '-1' to exit." << endl;
			cin >> player;

			if (player != 0 && player != 1 && player != -1) {
				cout << "INVALID ENTRY: Would you like to play another game ? Enter a '0' or '1' to play again, or enter '-1' to exit." << endl;
				cin >> player;
			}
		}
		cout << *this << endl;
	}

	/*
	* Description:	Determines if the value player is >= 0
	* Pre-Condition:	player is initialized with a value
	*
	* Post-Condition:	returns true if player is >= 0
	*/
	bool HangMan::keepPlaying(int player) {
		return player >= 0;
	}

	/*
	* Description:	Starts up the game and explains how to play
	* Pre-Condition:	game initialized
	*
	* Post-Condition:	difficulty is initalized with value this function returns
	*/
	int HangMan::gameStart() {
		int difficultyLvl = 0;

		while (difficultyLvl != 1 && difficultyLvl != 2 && difficultyLvl != 3) {
			cout << "Welcome to Hang Man, the object of this game is to correctly guess the word in less than 6 guess." << endl;
			cout << "Each turn you will pick a letter that may or may not be in the word." << endl;
			cout << "There are three difficulty levels: beginner, intermediate, and hard." << endl;
			cout << "Please make a selection: Enter 1 for beginner, 2 for intermediate, or 3 for expert." << endl;
			cin >> difficultyLvl;
		}
		printGameStart();
		return difficultyLvl;
	}

	/*
	* Description:	Determines the game mode that will be used during play
	* Pre-Condition:	A valid selection and difficulty has been initialized
	*
	* Post-Condition:	returns a file with a list of words, there are 3 modes
	*					Beginner, Intermediate, Expert
	*/
	ifstream HangMan::gameMode(bool selection, int difficulty) {
		ifstream words;

		if (selection) {
			switch (difficulty) {
			case 1:
				cout << "You have chosen Beginner Mode." << endl;
				words.open("Beginner.txt");
				break;
			case 2:
				cout << "You have chosen Intermediate Mode." << endl;
				words.open("Intermediate.txt");
				break;
			case 3:
				cout << "You have chosen Expert Mode." << endl;
				words.open("Expert.txt");
				break;
			default:
				break;
			}
			selection = false;
		}
		return words;
	}

	/*
	* Description:	Prints the beginning gameboard
	* Pre-Condition:	a valid difficulty has been selected
	*
	* Post-Condition:	The Hang Man board is displayed in the console
	*/
	void HangMan::printGameStart() {
		cout << "_______" << endl;
		cout << " |     |" << endl;
		cout << "       |" << endl;
		cout << "       |" << endl;
		cout << "       |" << endl;
		cout << "       |" << endl;
		cout << "_______|____" << endl;
	}

	/*
	* Description:	Determines if the selection is valid
	* Pre-Condition:	Difficulty is initialized
	*
	* Post-Condition:	returns true if difficulty is valid, in a range of 1 - 3
	*/
	bool HangMan::validSelection(int difficulty) {
		if (difficulty >= 1 && difficulty <= 3)
			return true;

		return false;
	}

	/*
	* Description:	get the word to be used during play from the chosen game mode
	*				database (chosen file) and puts the conent of the file into a vector
	*
	* Pre-Condition:	difficulty has been initialized and a valid file has been returned
	*
	* Post-Condition:	the vector has been filled and a random word is returned from the vector
	*/
	string HangMan::getWord(ifstream& file) {
		vector<string> words;
		string word;

		if (file.is_open()) {
			while (getline(file, word)) {
				stringstream line(word);
				string token;
				while (getline(line, token, ',')) {
					words.push_back(token);
				}
			}
			file.close();
		}
		if (!words.empty()) {
			srand(static_cast<unsigned int>(time(nullptr)));
			int randomGen = rand() % words.size();
			return words[randomGen];
		}
		else {
			return "";
		}
	}

	/*
	* Description:	Guess a letter, you have 6 max guesses
	*
	* Pre-Condition:	game elements are initialized for play
	*
	* Post-Condition:	pushes the characters guesses into the guesses vector to pass into the guess check
	*					every time a guess is wrong the guesscount will increment and output the correct
	*					gameboard
	*/
	int HangMan::guessLetter(string word, string& guessState, int& guessCount, int difficulty) {
		char guess = ' ';

		while (guessCount < MAXGUESS && guessState != word) {

			cout << "Please guess a letter in the word." << endl;
			cin >> guess;

			while (!isalpha(guess) || cin.get() != '\n') {
				cout << "INVALID ENTRY: " << endl;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');

				cout << "Please guess a letter in the word." << endl;
				cin >> guess;
			}

			if (word.find(toupper(guess)) == string::npos && word.find(tolower(guess)) == string::npos) {
				cout << "_______" << endl;
				cout << " |     |" << endl;
				guessCount++;

				switch (guessCount) {
				case 1:
					cout << " 0     |" << endl;
					cout << "       |" << endl;
					cout << "       |" << endl;
					break;
				case 2:
					cout << " 0     |" << endl;
					cout << "/      |" << endl;
					cout << "       |" << endl;
					break;
				case 3:
					cout << " 0     |" << endl;
					cout << "/|     |" << endl;
					cout << "       |" << endl;
					break;
				case 4:
					cout << " 0     |" << endl;
					cout << "/|\\    |" << endl;
					cout << "       |" << endl;
					break;
				case 5:
					cout << " 0     |" << endl;
					cout << "/|\\    |" << endl;
					cout << "/      |" << endl;
					break;
				case 6:
					cout << " 0     |" << endl;
					cout << "/|\\    |" << endl;
					cout << "/ \\    |" << endl;
					break;
				default:
					cout << "       |" << endl;
					cout << "       |" << endl;
					cout << "       |" << endl;
					break;
				}
				cout << "       |" << endl;
				cout << "_______|____" << endl;
				cout << guessCount << endl;

			}
			else {
				cout << "Your guess was correct, please continue." << endl;
				guesses.push_back(guess);
				guessState = checkGuess(word, guesses);

				cout << guessState << endl;
			}
		}
		gameOutcome(guessCount, word, guessState);

		return guessCount;
	}

	/*
	* Description:	Checks the guess and determines if the character guessed is in the word
	* Pre-Condition:	guessLetter has been initialized and the guess has been passed into checkGuess
	*
	* Post-Condition:	return the current state of the string word, displaying what characters are in the word
	*					and underscore will be shown for characters not yet guessed
	*/
	string HangMan::checkGuess(const string& word, const vector<char>& guesses) {
		string current = string(word.length(), '_');
		char letter;

		for (int i = 0; i < word.length(); i++) {
			letter = tolower(word[i]);

			if (find(guesses.begin(), guesses.end(), letter) != guesses.end()) {
				current[i] = letter;
			}
			else {
				current[i] = '_';
			}
		}
		if (!current.empty()) {
			current[0] = toupper(current[0]);
		}
		return current;
	}

	/*
	* Description:	Displays the outcome of the game when it ends
	* Pre-Condition:	The max guesses have been reached or the correct word has been guessed
	*
	* Post-Condition:	total losses and total wins are incremented to track rounds won and lost
	*/
	void HangMan::gameOutcome(int guessCount, const string& word, const string& guessedWord) {
		if (guessCount == MAXGUESS) {
			cout << "You did not win this round, thank you for playing. Please play again." << endl;
			totalLosses++;
		}
		else if (word == guessedWord) {
			cout << "The word was " << word << "! You have guessed correctly! Congratulations!" << endl;
			totalWins++;
		}
		else {
			cout << "Error, something went wrong.." << endl;
		}
	}

	/*
	* Description:	Prints underscores to display the length of the random word chosen for play
	* Pre-Condition:	game mode difficulty has been chosen, game is intialized
	*
	* Post-Condition:	displays underscores, one for each character in the word
	*/
	void HangMan::printLength(string& word) {
		for (char charCount : word) {
			cout << "_ ";
		}
		cout << endl;
	}

	/*
	* Description:	Overloads the << operator to display the Hangman object information
	* Pre-Condition:	HangMan object initialized
	*
	* Post-Condition:	displays the total wins, losses, and games played in the console
	*/
	ostream& operator<<(ostream& oStream, const HangMan& hangMan) {
		oStream << "Thank you for playing Hang Man! Please come back soon!" << endl;
		oStream << "Total wins: " << hangMan.totalWins << endl;
		oStream << "Total losses: " << hangMan.totalLosses << endl;
		oStream << "Total games played: " << hangMan.totalPlayed << endl;
		return oStream;
	}
}
