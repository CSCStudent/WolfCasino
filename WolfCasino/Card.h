#pragma once
#include <string>

namespace S02415179 {
	const std::string suitNames[]{ "C", "D", "H", "S" };

	class Card {
	public:
		int suit;
		int rank;
		Card(int, int);
		Card(const Card&);
		~Card() {};		//destructor, intentionally left blank

		void readCard();
	};

	//default constructor
	Card::Card(int suitV, int rankV) : suit(suitV), rank(rankV) {}

	//copy constructor
	Card::Card(const Card& tocopy) : suit(tocopy.suit), rank(tocopy.rank) {}

	//Function built to read out card in standard format using suit and rank values
	void Card::readCard() {
		//pre: card object must have suit and rank populated
		//post: prints out the interpreted suit and rank values in card format
		switch (rank) {
		case 1:
			std::cout << "A" << suitNames[suit];
			break;
		case 11:
			std::cout << "J" << suitNames[suit];
			break;
		case 12:
			std::cout << "Q" << suitNames[suit];
			break;
		case 13:
			std::cout << "K" << suitNames[suit];
			break;
		default:
			std::cout << rank << suitNames[suit];
		}
	}
}