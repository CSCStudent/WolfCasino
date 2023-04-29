#pragma once

#include <ctime>
#include "Casino.h"
#include <string>

namespace CSC2034
{
    // Enumeration to represent the suits of the game
    enum Suit {HEARTS, DIAMONDS, CLUBS, SPADES, JESTER, WIZARD};

    // Class to represent the card
    class Card
    {
    public:
        // Default constructor
        Card();

        // Constructor with arguments for rank and suit
        Card(int rank, Suit suit);

        // Destructor
        ~Card();

        // Getter functions for rank and suit
        int getRank() const;
        Suit getSuit() const;

    private:
        int rank;  // The rank of the card
        Suit suit; // The suit of the card
    };

    // Class to represent a deck of cards
    class Deck
    {
    public:
        // Constructor
        Deck();

        // Destructor
        ~Deck();

        // Function to shuffle the cards in the deck
        void shuffle();

        static const int NUM_CARDS = 60; // The number of cards in the deck
        Card cards[NUM_CARDS];           // An array of cards representing the deck
        

    private:
        
        
    };

    // Class to represent the Wizard card game
    class Wizard : public Casino
    {
    public:
        // Constructor
        Wizard();

        // Static factory method to create a new Wizard game
        static Wizard* makeGame();

        // Function to start the game
        void start();

    private:
        // Function to run a single round of the game
        void run();
    };
} //end of namespace CSC2034
