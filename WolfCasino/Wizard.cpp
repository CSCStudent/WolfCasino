#include <iostream>
#include "Wizard.h"

using namespace std;
using namespace CSC2034;

// Constructor
Wizard::Wizard()
{
      
}

// Static factory method to create a new Wizard game
Wizard* Wizard::makeGame()
{
    return new Wizard();
}

// Function to start the game
void Wizard::start()
{
    std::cout << "Starting a game of Wizard!" << std::endl;
    run();
}

// Function to run a single round of the game
void Wizard::run()
{
    std::cout << "Running a round of Wizard!" << std::endl;
}

// Default constructor sets the rank and suit to 0
Card::Card()
{
    rank = 0;
    suit = static_cast<Suit>(0);
}

// Constructor with arguments for rank and suit
Card::Card(int rank, Suit suit)
{
    this->rank = rank;
    this->suit = suit;
}

// Destructor
Card::~Card()
{
        
}

// Getter function for the rank of the card
int Card::getRank() const
{
    return rank;
}

// Getter function for the suit of the card
Suit Card::getSuit() const
{
    return suit;
}

// Constructor initializes the deck with all possible cards
Deck::Deck()
{
    int index = 0;
    for (int i = 1; i <= 14; i++)
    {
        for (int j = HEARTS; j <= SPADES; j++)
        {
            cards[index] = Card(i, static_cast<Suit>(j));
            index++;
        }
    }
    // Add jesters and wizards
    cards[index++] = Card(15, JESTER);
    cards[index++] = Card(15, WIZARD);
}

// Destructor
Deck::~Deck()
{

}

// Shuffle the cards in the deck using a simple swap algorithm
void Deck::shuffle()
{
    // Seed the random number generator with the current time
    srand(static_cast<unsigned int>(time(nullptr))); 

    for (int i = NUM_CARDS - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);
        Card temp = cards[i];
        cards[i] = cards[j];
        cards[j] = temp;
    }
}
