#pragma once
#include <vector>
#include "Deck.h"
#include "Card.h"

using namespace std;

class Hand {
private:
	std::vector<Card> hand;
	bool isSorted;

public:
	Hand();
	Hand(int, Deck&);
	~Hand() {};

	const Hand& addCard(Card);
	Hand& draw(int, Deck*);
	void readHand();
	void readHandNum();
	static bool compareCards(const Card&, const Card&);
	void sortHand();
	//Hand& muckCards(int, Deck*);
	//Hand& muckHand(Deck*);
};

Hand::Hand() : hand(), isSorted() {}

Hand::Hand(int amount, Deck& drawfrom) {
	this->draw(amount, &drawfrom);
	isSorted = false;
}

const Hand& Hand::addCard(Card toadd) {
	hand.push_back(toadd);
	isSorted = false;
	return *this;
}

Hand& Hand::draw(int amount, Deck* drawfrom) {
	for (unsigned int i = 0; i < amount; i++) {
		const Card& todraw = drawfrom->removeCard(0);
		this->addCard(todraw);
	}
	return *this;
}

void Hand::readHand() {
	for (int i = 0; i < this->hand.size()-1; i++) {
		this->hand[i].readCard();
	}
}

void Hand::readHandNum() {
	for (int i = 1; i < this->hand.size(); i++) {
		std::cout << i << ") ";
		this->hand[i].readCard();
	}
}

bool Hand::compareCards(const Card& card1, const Card& card2) {
	if (card1.rank < card2.rank)
		return true;
	else if (card1.rank == card2.rank)
		return (card1.suit < card2.suit);
	return false;
}

void Hand::sortHand() {
	for (unsigned int i = 0; i < this->hand.size()-1; i++) {
		for (unsigned int j = 0; j < this->hand.size() - i - 1; j++) {
			if (compareCards(this->hand[j], this->hand[j + 1]))
				swap(this->hand[j], this->hand[j + 1]);
		}
	}
}

//Hand& Hand::muckCards(int amount, Deck* muckto) {
//	int tomuck;
//	for (unsigned int i = 0; i < amount; i++) {
//		this->readHandNum();
//		std::cout << "Which card would you like to muck? Type the number corresponding to the card.\n";
//		std::cin >> tomuck;
//		const Card& mucking = this->hand[tomuck];
//		muckto->addCard(mucking);
//		this->hand.erase(this->hand.begin() + tomuck);
//	}
//	return *this;
//}
//
//Hand& Hand::muckHand(Deck* muckto) {
//	int size = this->hand.size();
//	this->muckCards(size, muckto);
//	return *this;
//}