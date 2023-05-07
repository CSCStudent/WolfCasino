#ifndef HAND_H
#define HAND_H
#include <vector>
//#include "Deck.h"
#include "Card.h"

class Hand {
private:
	std::vector<Card> hand; //Vector for holding dealer and player's hands
	bool bustFlag = false;
	bool splitFlag = false;
	bool aceSplitFlag = false;
	bool blackjackFlag = false;
	bool dealerFlag = false;
	bool doubleDownFlag;
	int handValue = 0; //Value of cards in hand
	int money = 0; //player or dealer funds

public:
	Hand();
	~Hand() {}; //default deconstructor

	const Hand& addCard(Card); //Add a card to hand
	Card removeTopCard(); //remove card from hand returns that card
	bool yesnotest(char); //test if value is 'y' or 'n' and returns bool answer if not one of those
	int handSize(); //size of hand vector
	int aceCount(); //how many aces are there in the hamd
	bool doubleDownPrompt(); //Do you want to double down? returns bool and sets flag
	bool doubleDownCheck(); //checks value of flag returns bool of same value
	void setMoney(int); //sets money for a hand object
	int getMoney(); //view money in hand object
	bool blackjackCheck(); //checks to see if you have two cards with a value of 21
	void setHandValue(); //assigns value of hand
	int getHandValue(); //hand value getter
	void readHandValue(); //prints instead of gets
	bool bustFlagCheck(); //flag checker
	void setDealerFlag(); //dealer flag for cout statements
	bool dealerFlagCheck(); //flag checer
	void topCard(); //show top card only (for dealer)
	void resetFlags(); //reset all flags to false
	void readHand(); //read cards in hand with handValue
};

//default constructor
Hand::Hand() : hand(), bustFlag(), splitFlag(), aceSplitFlag(), handValue(), money() {}

//returns the size of the hand vector
int Hand::handSize() {
	//Pre: requires a hand vector to exist
	//Post: returns an int of its size
	int hSize = hand.size();
	return hSize;
}

//Counts aces in hand for setValue function
int Hand::aceCount() {
	//pre: have a hand object
	//post:: returns an int of how many aces in hand
	int acesPresent = 0;
	for (int i = 0; i < this->hand.size(); i++) {
		if (this->hand[i].rank == 1)
			acesPresent++;
	}
	return acesPresent;
}

//addCard to hand
const Hand& Hand::addCard(Card toadd) {
	//pre: have a hand object and pass it a card object
	//post: adds card to hand object
	hand.push_back(toadd);
	return *this;
}

//pops top card from hand
Card Hand::removeTopCard() {
	//pre: must have a hand that has at least one card object in it
	//post: returns that card as an object and removes from hand
	Card temp = hand.back();
	hand.pop_back();
	return temp;
}

//test if char is 'y' or 'n'
bool Hand::yesnotest(char x) {
	//pre: requires a char passed to it
	//post: returns a bool if it is 'y' or 'n'
	if (x == 'y')
		return true;
	if (x == 'n')
		return true;
	return false;
}

//Check if player would like to double down. If so set double down flag, return that flag as a bool
bool Hand::doubleDownPrompt() {
	//pre: player must have hand
	//post: set doubleDownFlag if selected, return value as bool
	char doubleDown;
	std::cout << "Does the player want to double down? (type 'y' or 'n')\n";
	std::cin >> doubleDown;
	doubleDown = tolower(doubleDown);
	while (!yesnotest(doubleDown)) {
		std::cout << "Invalid input. (type 'y' or 'n')\n";
		std::cin >> doubleDown;
		doubleDown = tolower(doubleDown);
	}
	if (doubleDown == 'y') {
		std::cout << "Double down initiated!\n";
		doubleDownFlag = true;
		return true;
	}
	return false;
}

//Double down getter
bool Hand::doubleDownCheck() {
	//pre: must have a hand object
	//post: returns doubleDownFlag bool value
	return doubleDownFlag;
}

//money setter
void Hand::setMoney(int amount) {
	//pre: requires a hand object and an int passed to it
	//post: populates hand objects money with amount passed to it
	this->money = amount;
}

//money getter
int Hand::getMoney() {
	//pre: must have a hand object
	//post: returns hand's money int value
	return money;
}

//checks if player has blackjack
bool Hand::blackjackCheck() {
	//pre: requires hand object
	//post: returns bool value if blackjack witnessed or not
	setHandValue();
	if (handValue == 21)
		return true;
	return false;
}

//Function to assign value to hand
void Hand::setHandValue() {
	//pre: requires a hand object that is populated with cards
	//post: sets handValue and bustFlag if necessary
	//reset to 0 so adding a card does not double count cards
	handValue = 0;
	int howmanyaces = aceCount();

	//loop through hand and add values
	for (int i = 0; i < this->hand.size(); i++) {
		int cardValue = this->hand[i].rank;
		if (cardValue >= 10)
			handValue += 10;
		else if (cardValue != 1)
			handValue += cardValue;
		else if (cardValue == 1)
			handValue += 11;
	}
	//change ace value from 11 to 1 if that creates a bust
	while (handValue > 21 && howmanyaces > 0) {
		handValue -= 10;
		howmanyaces--;
	}
	//set bustFlag if player busted
	if (handValue > 21)
		bustFlag = true;
}

//hand value getter
int Hand::getHandValue() {
	//pre: requires a hand object with cards to exist
	//post: returns handValue of hand
	return this->handValue;
}

//hand value reader
void Hand::readHandValue() {
	//pre: requires a hand object with cards to exist
	//post: prints handValue of hand
	std::cout << this->handValue;
}

//Bustflag getter
//operates by counting handvalue and letting that function set bustFlag value.
bool Hand::bustFlagCheck() {
	//pre: must have a hand object which is populated
	//post: returns whether hand is a bust or not (bool)
	this->setHandValue();
	return bustFlag;
}

//Set dealer flag, just used for some output commands
void Hand::setDealerFlag() {
	//pre: have a hand object populated
	//post: sets dealer's hand object dealerFlag to true
	dealerFlag = true;
}

//dealerFlag getter
bool Hand::dealerFlagCheck() {
	//pre: hand object exists
	//post: returns whether that object belongs to dealer (bool)
	return dealerFlag;
}

//shows top card of hand, dealers visible card
void Hand::topCard() {
	//pre: hand object must be populated for dealer (only used by that in CardGame.h
	//post: prints value of the top card
	this->hand[0].readCard();
}

//flag setter to be ran in between every hand
void Hand::resetFlags() {
	//pre: must have hand object
	//post: sets hand object flags all to false (other than dealer)
	bustFlag = false;
	splitFlag = false;
	aceSplitFlag = false;
	blackjackFlag = false;
}

//Print out function to see player/dealers complete hand
void Hand::readHand() {
	//pre: requires hand object to be populated with card objects
	//post: prints out hand using loop
	for (int i = 0; i < this->hand.size(); i++) {
		this->hand[i].readCard();
		std::cout << " ";
	}
	this->setHandValue();
	this->readHandValue();
}
#endif // HAND_H