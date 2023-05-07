#pragma once
#include <string>

const std::string suitNames[]{ "C", "D", "H", "S", "Joker???"};

class Card {
public:
	int suit;
	int rank;
	Card(int, int);
	Card(const Card&);
	~Card() {};		//destructor, intentionally left blank

	void readCard();
};

Card::Card(int suitV, int rankV) : suit(suitV), rank(rankV) {}

Card::Card(const Card& tocopy) : suit(tocopy.suit), rank(tocopy.rank){}

//Function built to read out card in standard format using suit and rank values
void Card::readCard() {
	switch (rank) {
	case 1:
		std::cout << "A" << suitNames[suit] << std::endl;
		break;
	case 11:
		std::cout << "J" << suitNames[suit] << std::endl;
		break;
	case 12:
		std::cout << "Q" << suitNames[suit] << std::endl;
		break;
	case 13:
		std::cout << "K" << suitNames[suit] << std::endl;
		break;
	default:
		std::cout << rank << suitNames[suit] << std::endl;
	}

}