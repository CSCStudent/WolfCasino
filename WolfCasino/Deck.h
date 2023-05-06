#pragma once
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <vector>
#include "Card.h"

class Deck {
private:
	std::vector<Card> deck;
	std::vector<Card> discardPile;
	//int cardCount = 0;

public:
	Deck();
	Deck(int, int);			//Constructor for normal deck of cards is Deck(13, 4)
	Deck(int);				//Consctructor for multiple normal decks, i.e. (4) creates a deck with four decks inside of it
	Deck(const Deck&);
	~Deck() {};				//Destructor, left blank intentionally

	Deck shuffle(Deck&);			//Just shuffles the deck
	Deck mergeDeck();
	Deck shuffleFull();		//Shuffles deck and discard pile
	void addCard(const Card&);
	void millCard(int);
	const Card& removeCard(int);
	void readDeck();	//Show all the cards in the deck.
};

Deck::Deck() : deck(), discardPile() {}

Deck::Deck(int x, int y) {
	for (unsigned int i = 0; i < x; i++) {
		for (unsigned int j = 1; j < y + 1; j++) {
			deck.push_back(Card(i, j));
		}
	}
}

Deck::Deck(int x) {
	for (int i = 0; i < x; i++) {
		Deck subDeck(4, 13);
		for (Card card : subDeck.deck) {
			deck.push_back(card);
		}
	}
}

Deck::Deck(const Deck& tocopy) : deck(tocopy.deck), discardPile(tocopy.discardPile){}

Deck Deck::shuffle(Deck& toshuffle) {
	srand(time(NULL));
	Deck* tempDeck = new Deck();
	while (!toshuffle.deck.empty()) {
		int randIndex = rand() % toshuffle.deck.size();
		Card randCard = toshuffle.deck[randIndex];
		toshuffle.removeCard(randIndex);
		tempDeck->addCard(randCard);
	}
	toshuffle.deck = tempDeck->deck;
	delete tempDeck;
	return toshuffle;
	/*srand(time(NULL));
	for (int i = 0; i < deck.size(); i++) {
		int randV = rand() % deck.size();
		Card temp = deck[i];
		deck[i] = deck[randV];
		deck[randV] = temp;
	}
	return *this;*/
}

Deck Deck::mergeDeck() {
	deck.insert(deck.end(), discardPile.begin(), discardPile.end());
	discardPile.clear();
	return *this;
}

Deck Deck::shuffleFull() {
	this->mergeDeck();

	return this->shuffle(*this);
}

void Deck::addCard(const Card& addme) {
	deck.push_back(addme);
}

void Deck::millCard(int x) {
	for (int i = 0; i < x; i++) {
		Card temp = deck[deck.size()-i-1];
		this->deck.pop_back();
		this->discardPile.push_back(temp);
	}
}

const Card& Deck::removeCard(int index) {
	if (index < 0 || index >= deck.size()) {
		throw std::out_of_range("Index out of range!");
	}
	Card* card = &deck[index];
	deck.erase(deck.begin() + index);
	return *card;
}

//Reads out all the cards in the discard pile and card pile
void Deck::readDeck() {
	if (this->deck.size() == 0) 
		std::cout << "Empty deck." << endl;
	if (this->deck.size() != 0) {
		int deckSize = this->deck.size();
		std::cout << deckSize <<" cards in deck:" << endl;
		for (Card card : this->deck)
			card.readCard();
	}
	if (this->discardPile.size() == 0)
		std::cout << "Empty discard pile." << endl;
	if (this->discardPile.size() != 0) {
		int dpSize = this->discardPile.size();
		std::cout << dpSize << " cards in discard pile:" << endl;
		for (Card card : this->discardPile)
			card.readCard();
	}
}