#ifndef DECK_H
#define DECK_H
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <vector>
#include "Card.h"
#include "Hand.h"

namespace S02415179 {
	class Deck {
	private:
		std::vector<Card> deck; //primary deck
		std::vector<Card> discardPile; //discard pile for in between deck shuffles
		bool handDone = false;
		bool resignGame = false;

	public:
		Hand dealer;
		Hand player;
		Deck();
		Deck(int, int);			//Constructor for normal deck of cards is Deck(13, 4)
		Deck(int);				//Consctructor for multiple normal decks, i.e. (4) creates a deck with four decks inside of it
		Deck(const Deck&);
		~Deck() {};				//Destructor, left blank intentionally

		Deck shuffle();			//Just shuffles the deck
		Deck mergeDeck();		//merges deck and discard pile
		Deck shuffleFull();		//Shuffles deck and discard pile
		void initializeMoney(); //sets money value for player and dealer
		void addCard(const Card&); //adds card to deck object
		void dealCard(int, Hand&); //moves card from deck object to hand object
		void setHandDone(bool); //flag that player is not going to hit anymore
		bool handDoneCheck(); //handDone getter
		void deckRemaining(); //checks how many cards are left in the deck versus discard pile, used to determine when to shuffle back together
		void discardHand(); //moves cards from player and dealer to discardpile
		const Card& removeCard(int); //removes a card from deck object and returns it
		void handAfterHit(Hand); //displays entire hand and labels whose hand it belongs to
		void boardState(); //prints board state of player and dealer after dealing
		void moneyCheck(); //prints dealer and player money
		void readDeck();	//Show all the cards in the deck (for testing)
		void setResignGame(); //resignGameFlag setter
		bool resignGameCheck(); //resignGameFlag getter
		void resetHands(); //resets flags for dealer, player and handDome
		bool gameOverCheck(); //somebody has run out of money
	};

	//default constructor
	Deck::Deck() : deck(), discardPile() {}

	//constructor for creating 52 card dekc using (4,13)
	//can create decks of other size/suit amounts
	Deck::Deck(int x, int y) {
		//pre: card objects must exist and be defined
		//post: creates a vector of card objects
		for (int i = 0; i < x; i++) {
			for (int j = 1; j < y + 1; j++) {
				deck.push_back(Card(i, j));
			}
		}
		//sets dealer flag for dealer hand object
		if (dealer.dealerFlagCheck() != true)
			dealer.setDealerFlag();
	}

	//constructor for creating a deck of multiple decks
	Deck::Deck(int x) {
		//pre: deck(int, int) constructor must exist and card objects must be defined
		//post: creates a vector of card objects
		for (int i = 0; i < x; i++) {
			Deck subDeck(4, 13);
			for (Card card : subDeck.deck) {
				deck.push_back(card);
			}
		}
	}

	//copy constructor
	Deck::Deck(const Deck& tocopy) : deck(tocopy.deck), discardPile(tocopy.discardPile) {}

	//Shuffle deck function, just shuffles objects in the deck vector
	Deck Deck::shuffle() {
		//pre: deck vector must exist
		//post: assigns a quasi-random positioning to features inside and returns that object
		srand(time(NULL));
		Deck* tempDeck = new Deck();
		while (!deck.empty()) {
			int randIndex = rand() % deck.size();
			Card randCard = deck[randIndex];
			removeCard(randIndex);
			tempDeck->addCard(randCard);
		}
		deck = tempDeck->deck;
		delete tempDeck;
		return *this;
	}

	//moves all card objects from the discardPile to the deck
	Deck Deck::mergeDeck() {
		//pre: Deck object exists and is populated with Card objects
		//post: combines discardPile and deck, moves Card objects from one to the other
		deck.insert(deck.end(), discardPile.begin(), discardPile.end());
		discardPile.clear();
		return *this;
	}

	//helper routing to shuffle deck after it has been merged with discardpile
	Deck Deck::shuffleFull() {
		//pre: deck object exists and its deck object or discardpile object is popualted
		//post: returns a quasi-random shuffling of the two
		this->mergeDeck();
		return this->shuffle();
	}

	//Function to set player and dealer money at beginning of game
	void Deck::initializeMoney() {
		//pre: deck object exists
		//post: populates dealer.money and player.money
		this->dealer.setMoney(400); //dealer always gets 400 to start
		int thisMuch = 0;
		int count = 0;

		//ugly text box, can do with cleanup
		std::cout << "\nWelcome to Henry's blackjack game!\n\n";
		while (thisMuch < 50 || thisMuch > 500) {
			if (count == 0) {
				std::cout << "Each ante is 10 dollars. How much money would you like to start with?\nThe dealer starts with 400. 200 is recommended.\n";
				std::cin >> thisMuch;
			}
			else {
				std::cout << "Please input a value between 50 and 500.\n";
				std::cin >> thisMuch;
			}
			if (thisMuch < 50)
				std::cout << "Please start with at least 50.\n";
			if (thisMuch > 500)
				std::cout << "Please start with less than 500.\n";
			count++;
		}
		int antes = thisMuch / 10;
		this->player.setMoney(thisMuch);
		std::cout << "You have " << thisMuch << " dollars. This means you have " << antes << " antes available.\n\nLet's get this started! ";
		system("pause"); //pause system for style points
		std::cout << "\n\n";
	}

	//add card passed to deck object
	void Deck::addCard(const Card& addme) {
		//pre: deck object exists
		//post: card passed to function is added to deck at back
		deck.push_back(addme);
	}

	//functions that takes cards from deck vector and adds to dealer or player hand
	void Deck::dealCard(int x, Hand& dealhere) {
		//pre: must have a deck vector popualted with cards and a hand to deal to
		//post: removes cards from top of deck vector adds to Hand object
		//if players don't have any cards yet and deck is getting slim, reshuffle deck and discardpile
		if (dealer.handSize() == 0 && player.handSize() == 0)
			deckRemaining();
		int deckSize = int(deck.size()); //set to int otherwise changes values every loop. that took a while to figure out
		for (int i = 0; i < x; i++) {
			Card temp = deck[deckSize - i - 1];
			this->deck.pop_back();
			dealhere.addCard(temp);
		}
	}

	//handDoneSetter - used to determine when it is dealer's turn
	void Deck::setHandDone(bool finished) {
		handDone = finished;
	}

	//handDoneChecker - used to read when players hand is in its final state
	bool Deck::handDoneCheck() {
		return handDone;
	}

	//tests to see if discardpile is 3 times larger than deck. If so it shuffles them together back into the deck
	void Deck::deckRemaining() {
		//pre: must have a deck or discardpile vector populated with cards
		//post: moves all cards to deck and shuffles (only called when players have no cards in hand)
		if ((3 * deck.size()) < discardPile.size()) {
			shuffleFull();
			std::cout << "Restart your card counters, discard pile shuffled into deck.\n";
		}
	}

	//moves cards from dealers and players hand objects to discardpile
	void Deck::discardHand() {
		//pre: hand and dealer must have hand objects populated with cards
		//post: removes card objects from Hand objects and adds to discardpile, resets handflags since this is mark of beginning of next hand
		int dHS = dealer.handSize();
		for (int i = 0; i < dHS; i++) {
			discardPile.push_back(dealer.removeTopCard());
		}
		dealer.resetFlags();
		int pHS = player.handSize();
		for (int i = 0; i < pHS; i++) {
			discardPile.push_back(player.removeTopCard());
		}
		player.resetFlags();
	}

	//function to remove a card from the deck and return it as an object
	const Card& Deck::removeCard(int index) {
		//pre: deck object must exist and be populated with card objects
		//post: removes card from deck and returns it as an object
		if (index < 0 || index >= deck.size()) {
			throw std::out_of_range("Index out of range!");
		}
		Card* card = &deck[index];
		deck.erase(deck.begin() + index);
		return *card;
	}

	//function to read players hands, says who hand belongs to
	void Deck::handAfterHit(Hand readhand) {
		//pre: dealer and player hand objects must exist
		//post: reads hand and says who it belongs to
		if (!readhand.dealerFlagCheck())
			std::cout << "Cards in hand:" << std::endl;
		if (readhand.dealerFlagCheck())
			std::cout << "Dealer's hand:" << std::endl;
		readhand.readHand();
	}

	//function to print board state after initial dealing of cards
	void Deck::boardState() {
		//pre: Deck object exists with populated player and dealer Hand objects
		//post: displays Hand object contents, only top card for dealer unless blackjack per blackjack rules
		if (this->player.handSize() == 0)
			std::cout << "Player has no cards in hand." << std::endl;
		if (this->player.handSize() != 0) {
			player.setHandValue();
			std::cout << "Cards in hand:" << std::endl;
			this->player.readHand();
			cout << std::endl;
		}
		if (this->dealer.handSize() == 0)
			std::cout << "Empty dealer hand.\n" << std::endl;
		if (this->dealer.handSize() != 0) {
			dealer.setHandValue();
			if (dealer.getHandValue() != 21) {
				std::cout << "Dealer's top card:" << std::endl;
				this->dealer.topCard();
				std::cout << std::endl;
			}
			else {
				std::cout << "Dealer has blackjack.\n";
				this->dealer.readHand();
				std::cout << std::endl;
			}
		}
	}

	//moneyvalue getter
	void Deck::moneyCheck() {
		//pre: Deck object exists
		//post: returns player.money and dealer.money
		std::cout << "You have $" << player.getMoney() << std::endl;
		std::cout << "Dealer has $" << dealer.getMoney() << std::endl;
	}

	//Reads out all the cards in the discard pile and card pile, only used for testing
	void Deck::readDeck() {
		//pre: Deck object exists and is popualted
		//post: reveals deck object contents and ordering
		if (this->deck.size() == 0)
			std::cout << "Empty deck." << std::endl;
		if (this->deck.size() != 0) {
			int deckSize = int(this->deck.size());
			std::cout << "There are " << deckSize << " cards in deck:" << std::endl;
			int counter = 0;
			for (Card card : this->deck) {
				card.readCard();
				std::cout << " ";
				counter++;
				if (counter % 13 == 0)
					std::cout << std::endl;
			}
			if (counter % 13 != 0)
				std::cout << std::endl;
		}
		if (this->discardPile.size() == 0)
			std::cout << "Empty discard pile." << std::endl;
		if (this->discardPile.size() != 0) {
			int dpSize = int(this->discardPile.size());
			std::cout << "There are " << dpSize << " cards in discard pile:" << std::endl;
			int counter = 0;
			for (Card card : this->discardPile) {
				card.readCard();
				std::cout << " ";
				counter++;
				if (counter % 13 == 0)
					std::cout << std::endl;
			}
			if (counter % 13 != 0)
				std::cout << std::endl;
		}
		if (this->player.handSize() == 0)
			std::cout << "Empty player hand." << std::endl;
		if (this->player.handSize() != 0) {
			int dpSize = int(this->player.handSize());
			std::cout << "There are " << dpSize << " cards in your hand:" << std::endl;
			this->player.readHand();
			std::cout << std::endl;
		}
		if (this->dealer.handSize() == 0)
			std::cout << "Empty dealer hand.\n" << std::endl;
		if (this->dealer.handSize() != 0) {
			int dpSize = int(this->dealer.handSize());
			std::cout << "There are " << dpSize << " cards in the dealer's hand:" << std::endl;
			this->dealer.readHand();
			std::cout << std::endl;
		}
	}

	//resignGameSetter
	void Deck::setResignGame() {
		resignGame = true;
	}

	//resignGameGetter
	bool Deck::resignGameCheck() {
		return resignGame;
	}

	//function to reset flags for both players hands
	void Deck::resetHands() {
		//pre: Deck object must exist
		//post: sets Deck.player and Deck.dealer flags to False, sets deck flag to false
		this->player.resetFlags();
		this->dealer.resetFlags();
		this->handDone = false;
	}

	//Function to check if dealer or player ran out of money
	bool Deck::gameOverCheck() {
		//pre: Deck object must exist and intializeMoney() must be run
		//post: determines if either the dealer or player is out of money and returns that as a bool
		if (dealer.getMoney() <= 9) {
			std::cout << "You win! The dealer is out of money.\n";
			return true;
		}
		else if (player.getMoney() <= 9) {
			std::cout << "You lose... Not enough money for another ante.\n";
			return true;
		}
		return false;
	}
}
#endif // DECK_H