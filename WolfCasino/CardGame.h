#include <iostream>
#include "Hand.h"
#include "Card.h"
#include "Deck.h"
#include "Casino.h"

namespace CSC2034 {
	using namespace S02415179;
	class CardGame :public Casino {
	public:
		static CardGame* makeGame();
		void start();
		void run();
		void checkforblackjack(Deck);
		void winSequence(Deck, Hand, Hand);
		void resignSequenceTest(Deck);
		void test();
	};
}
 
namespace CSC2034 {
	CardGame* CardGame::makeGame() {
			return new CardGame;
	}
	void CardGame::start() {
		run();
	}

	//Primary code for blackjack game
	void CardGame::run() {
		Deck fourDeck(4); //Creates four decks in one
	newGame:
		fourDeck.initializeMoney(); //Sets money for player and dealer
		fourDeck.shuffleFull();
		fourDeck.moneyCheck();

		//Primary loop, ends when winner declared or player resigns
		while (!fourDeck.gameOverCheck() && !fourDeck.resignGameCheck()) {
			fourDeck.dealCard(2, fourDeck.player); //deal cards to player
			fourDeck.dealCard(2, fourDeck.dealer); //deal cards to dealer
			fourDeck.boardState();
			checkforblackjack(fourDeck); //Check for blackjacks
			
			//Loop for player to keep hitting until happy or busted
			if (!fourDeck.handDoneCheck()) {
				int counter = 0;
				char hitme;
				
				//Only offer the double-down on the first hit (use of counter var)
				if (counter == 0) {
					counter++;
					if (fourDeck.player.doubleDownPrompt()) {
						//If opted to double down deal one more card, check for bust and set hand to done always.
						fourDeck.dealCard(1, fourDeck.player);
						fourDeck.handAfterHit(fourDeck.player);
						if (fourDeck.player.bustFlagCheck()) {
							std::cout << "\nOops, looks like you busted.\n";
							winSequence(fourDeck, fourDeck.dealer, fourDeck.player);
						}
						else
							fourDeck.setHandDone(true);
					}
				}

				//Option to hit for another card if double-down declined.
				//Ends when handDoneFlag turned true
				if (!fourDeck.handDoneCheck()) {
					std::cout << "Would you like another card? (type 'y' or 'n')\n";
					std::cin >> hitme;
					hitme = tolower(hitme);
					while (!fourDeck.player.yesnotest(hitme)) {
						std::cout << "Invalid input. (type 'y' or 'n')\n";
						std::cin >> hitme;
						hitme = tolower(hitme);
					}
					switch (hitme) {
					case 'y':
						fourDeck.dealCard(1, fourDeck.player);
						fourDeck.handAfterHit(fourDeck.player);
						if (fourDeck.player.bustFlagCheck()) {
							std::cout << "\nOops, looks like you busted.\n";
							winSequence(fourDeck, fourDeck.dealer, fourDeck.player);
						}
						break;
					case 'n':
						std::cout << "Dealer's turn.\n";
						fourDeck.setHandDone(true);
					}
				}
			}
			//Blank if statement to avoid going into dealers turn if bustFlag is already true
			if (fourDeck.player.bustFlagCheck()) {
				//Left blank
			}

			//Dealer's turn
			else {
				fourDeck.handAfterHit(fourDeck.dealer); //Reveal dealers whole hand

				//Have healer hit if hand value less than 17
				while (fourDeck.dealer.getHandValue() < 17) {
					fourDeck.dealCard(1, fourDeck.dealer);
					fourDeck.handAfterHit(fourDeck.dealer);
					if (fourDeck.dealer.bustFlagCheck()) {
						std::cout << "\nDealer busts!\n";
						winSequence(fourDeck, fourDeck.player, fourDeck.dealer);
					}
				}

				//If both dealer and player did not bust compare their hands
				if (!fourDeck.handDoneCheck()) {
					//draw sequence
					if (fourDeck.dealer.getHandValue() == fourDeck.player.getHandValue()) {
						std::cout << "Both dealer and player have same value. Split pot.\n";
						fourDeck.discardHand();
						fourDeck.moneyCheck();
						fourDeck.setHandDone(true);
					}
					//lose sequence
					else if (fourDeck.dealer.getHandValue() > fourDeck.player.getHandValue())
						winSequence(fourDeck, fourDeck.dealer, fourDeck.player);
					//win sequence
					else
						winSequence(fourDeck, fourDeck.player, fourDeck.dealer);
				}
			}
			//Reset all flags and discard hands to discard pile before starting new hand
			fourDeck.discardHand();
			fourDeck.resetHands();
		}
		if (fourDeck.dealer.getMoney() < 10)
			std::cout << "Congrats you beat the dealer!\n";
		else
			std::cout << "You are out of cash! Better luck next time.\n";

		//Check to see if player would like to play again.
		char goagain;
		std::cout << "Would you like to play again? (type 'y' or 'n')\n";
		std::cin >> goagain;
		while (!fourDeck.player.yesnotest(goagain)) {
			std::cout << "Not a valid input.\n";
			std::cin >> goagain;
			goagain = tolower(goagain);
		}
		if (goagain == 'y')
			goto newGame;
		std::cout << "Thanks for playing!";
	}

	//This function runs before giving option to hit. Checks for blackjacks and if found initiates winsequence or drawsequence
	void CardGame::checkforblackjack(Deck deck1) {
		//Pre-condition: We must have a deck, a dealer and a player with cards
		//Post-condition: If there is a blackjack this will initiate winsequence or drawsequence
		bool bjcheckplayer = deck1.player.blackjackCheck();
		bool bjcheckdealer = deck1.dealer.blackjackCheck();
		if (bjcheckplayer && bjcheckdealer) {
			std::cout << "Both dealer and player get blackjacks. Split pot.\n";
			deck1.discardHand();
			deck1.moneyCheck();
			deck1.setHandDone(true);
		}
		else if (bjcheckplayer) {
			std::cout << "Player wins hand with a blackjack!\n";
			winSequence(deck1, deck1.player, deck1.dealer);
		}
		else if (bjcheckdealer) {
			std::cout << "Dealer wins hand with a blackjack!\n";
			winSequence(deck1, deck1.dealer, deck1.player);
		}
	}

	//This function is used to abort the game before there is a declared winner.
	void CardGame::resignSequenceTest(Deck deck2) {
		//Pre-condition: None really
		//Post-condition: this will set the resigngame flag to true
		char badtypertest;
		std::cout << "Do you wish to keep playing? (type 'y' or 'n')";
		std::cin >> badtypertest;
		badtypertest = tolower(badtypertest);
		if (badtypertest == 'n')
			deck2.setResignGame();
	}

	//This sequence is intended to be used when a player wins a hand. It will move the necessary funds from the loser to the winner, discard the hands, reprint funds and setHandDone/resigncheck
	void CardGame::winSequence(Deck thisdeck, Hand winner, Hand loser) {
		//Pre-Condition: We must have a deck, a dealer and a player with cards and a winning hand.
		//Post-Condition: This will reallot money from the loser to the winner and discard players hands into discard pile. Also sets hand done and performs a resigncheck
		int amount = 10;
		if (thisdeck.player.doubleDownCheck() == true) //payout double for doubledown
			amount *= 2;
		if (thisdeck.player.blackjackCheck() == true) //payout 1.5 for blackjack
			amount += 5;
		int winnerspurse = winner.getMoney() + amount;
		int loserspurse = loser.getMoney() - amount;
		winner.setMoney(winnerspurse); // WHY DOESN'T THIS WORK???
		loser.setMoney(loserspurse); // WHY DOESN'T THIS WORK???
		thisdeck.discardHand(); //Does not appear to work
		thisdeck.moneyCheck(); //this does work but returns 0.0????
		thisdeck.setHandDone(true); // Why doesn't this work???
		resignSequenceTest(thisdeck);
	}


	//Testing function
	//Call in CardGame::start() instead of calling CardGame::run() if you want to use this
	void CardGame::test() {
		//Test constructors for one deck and multiple decks
		Deck oneDeck(4, 13);
		//Deck fourDeck(4);
		//std::cout << "One deck:" << std::endl;
		//oneDeck.readDeck();
		//std::cout << "Four decks:" << std::endl;
		//fourDeck.readDeck(fourDeck);

		////Test shuffle()
		//oneDeck.readDeck();
		//oneDeck.shuffle();
		//oneDeck.readDeck();
		oneDeck.initializeMoney();

		//Test shuffleFull()
		oneDeck.shuffleFull();
		//oneDeck.readDeck();
		oneDeck.dealCard(2, oneDeck.player);
		oneDeck.dealCard(2, oneDeck.dealer);
		//oneDeck.readDeck();
		oneDeck.boardState();
		//oneDeck.discardHand();
		//oneDeck.readDeck();
	}
}