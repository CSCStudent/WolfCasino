// Aaron Johnson
// S02440716

#ifndef BLACKJACK_H
#define BLACKJACK_H

#include <vector>
#include <string>
#include "Casino.h"

enum class Suit {
    CLUBS,
    DIAMONDS,
    HEARTS,
    SPADES
};

enum class Rank {
    ACE = 1,
    TWO,
    THREE,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
    NINE,
    TEN,
    JACK,
    QUEEN,
    KING
};


struct Card {
    Suit suit;
    Rank rank;

    std::string toString() const {
        std::string suitStr;
        switch (suit) {
            case Suit::CLUBS:
                suitStr = "Clubs";
                break;
            case Suit::DIAMONDS:
                suitStr = "Diamonds";
                break;
            case Suit::HEARTS:
                suitStr = "Hearts";
                break;
            case Suit::SPADES:
                suitStr = "Spades";
                break;
        }

        std::string rankStr;
        switch (rank) {
            case Rank::ACE:
                rankStr = "Ace";
                break;
            case Rank::JACK:
                rankStr = "Jack";
                break;
            case Rank::QUEEN:
                rankStr = "Queen";
                break;
            case Rank::KING:
                rankStr = "King";
                break;
            default:
                rankStr = std::to_string(static_cast<int>(rank));
                break;
        }

        return rankStr + " of " + suitStr;
    }
};


class Deck {
    public:
        Deck();
        void shuffle();
        Card draw();
        vector<Card> cards;
};

namespace CSC2034 {

    class Blackjack : public Casino {
        public:
            Blackjack();
            
            static Blackjack* makeGame();

            void start();

        private:
            int calculateHandValue(vector<Card> hand);
            vector<Card> playerHand;
            vector<Card> dealerHand;
    };

}

#endif // BLACKJACK_H
