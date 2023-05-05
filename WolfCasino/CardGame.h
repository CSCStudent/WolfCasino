#include <iostream>
#include "Hand.h"
#include "Card.h"
#include "Deck.h"
#include "Casino.h"

namespace CSC2034 {

	class CardGame :public Casino {
	public:
		void start();
		void run();
		static CardGame* makeGame();
	};
}
 
namespace CSC2034 {
	CardGame* CardGame::makeGame() {
			return new CardGame;
	}
	void CardGame::start() {
		run();
	}

	void CardGame::run() {
		//Test constructors for one deck and multiple decks
		Deck oneDeck(4, 13);
		Deck fourDeck(4);
		//std::cout << "One deck:" << std::endl;
		//oneDeck.readDeck();
		//std::cout << "Four decks:" << std::endl;
		//fourDeck.readDeck(fourDeck);

		////Test shuffle()
		//oneDeck.readDeck();
		//oneDeck.shuffle();
		oneDeck.readDeck();

		//Test millCard()
		oneDeck.millCard(5);
		oneDeck.readDeck();

		//Test shuffleFull()
		oneDeck.shuffleFull();
		oneDeck.readDeck();
	}

}
