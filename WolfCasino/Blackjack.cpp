// Aaron Johnson
// S02440716

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Blackjack.h"

namespace S02440716 {
    using namespace CSC2034;
    using namespace std;

    Blackjack::Blackjack() {
        cout << "Welcome to Blackjack" << endl;
    }

    Blackjack* Blackjack::makeGame() {
        return new Blackjack();
    }

    void Blackjack::start() {
        bool playAgain = false;
        Deck deck;
        Card draw;

        do {
            // start a new game
            deck = Deck(); // create a new deck
            deck.shuffle(); // shuffle the deck
            playerHand.clear(); // clear the player's hand
            dealerHand.clear(); // clear the dealer's hand

            // Deal starting cards
            draw = deck.draw();
            playerHand.push_back(draw);
            draw = deck.draw();
            dealerHand.push_back(draw);
            draw = deck.draw();
            playerHand.push_back(draw);
            draw = deck.draw();
            dealerHand.push_back(draw);

            // print each card in the player's hand
            cout << "\nPLAYER HAND:" << endl;
            for (Card card : playerHand) {
                cout << card.toString() << endl;
            }

            // print the first card in the dealer's hand
            cout << "\nDEALER HAND:" << endl;
            cout << dealerHand[0].toString() << endl;
            cout << "Hidden Card" << endl; // print a message for the hidden card

            bool playerTurn = true;
            bool dealerTurn = true;
            while (playerTurn || dealerTurn) {
                if (playerTurn) {
                    // player's turn
                    cout << "\nYour turn! (H)it or (S)tand?" << endl;
                    char input;
                    cin >> input;
                    if (tolower(input) == 'h') { // if the player chooses to hit
                        draw = deck.draw(); // draw a card from the deck
                        playerHand.push_back(draw); // add the card to the player's hand
                        cout << "You drew a " << draw.toString() << endl; // print the drawn card
                        if (calculateHandValue(playerHand) > 21) { // check if the player busts
                            cout << "Bust! You lose." << endl;
                            dealerTurn = false;
                            playerTurn = false;
                            break;
                        }
                    }
                    else { // if the player chooses to stand
                        playerTurn = false;
                    }
                }

                if (dealerTurn) {
                    // dealer's turn
                    cout << "\nDealer's turn..." << endl;
                    cout << "\nDealer's hand:" << endl;
                    for (Card card : dealerHand) {
                        cout << card.toString() << endl; // print each card in the dealer's hand
                    }
                    int dealerValue = calculateHandValue(dealerHand);
                    if (dealerValue < 17) { // if the dealer's hand is less than 17
                        cout << "\nDealer hits." << endl;
                        draw = deck.draw(); // draw a card from the deck
                        dealerHand.push_back(draw); // add the card to the dealer's hand
                        if (calculateHandValue(dealerHand) > 21) { // check if the dealer busts
                            cout << "Dealer busts! You win." << endl;
                            dealerTurn = false;
                            playerTurn = false;
                            break;
                        }
                    }
                    else { // if the dealer's hand is greater than or equal to 17
                        cout << "Dealer stands." << endl;
                        dealerTurn = false;
                    }
                }
            }

            // Determine winner
            if (calculateHandValue(playerHand) <= 21 && (calculateHandValue(playerHand) > calculateHandValue(dealerHand) || calculateHandValue(dealerHand) > 21)) {
                cout << "You win!" << endl;
            }
            else {
                cout << "You lose." << endl;
            }

            // Prompt to play again
            char input;
            cout << "\nPlay again? (Y)es or (N)o." << endl;
            cin >> input;
            playAgain = tolower(input) == 'y';

        } while (playAgain);
    }

    // Calculate the total value of a hand of cards in blackjack, including ace handling
    int Blackjack::calculateHandValue(vector<Card> hand) {
        int value = 0;
        int numAces = 0;

        // Loop through each card in the hand
        for (Card card : hand) {
            // Check the rank of the card and add the appropriate value to the total
            if (card.rank == Rank::ACE) {
                numAces++;
            }
            else if (card.rank == Rank::JACK || card.rank == Rank::QUEEN || card.rank == Rank::KING) {
                value += 10;
            }
            else {
                value += static_cast<int>(card.rank);
            }
        }

        // Handle aces as 1 or 11 based on the total value of the hand
        while (numAces > 0) {
            if (value + 11 <= 21) {
                value += 11;
            }
            else {
                value += 1;
            }
            numAces--;
        }

        // Return the total value of the hand
        return value;
    }

    // Constructor for the Deck class
    Deck::Deck() {
        for (int suit = 0; suit < 4; suit++) {
            for (int rank = 1; rank <= 13; rank++) {
                Card card = { static_cast<Suit>(suit), static_cast<Rank>(rank) };
                cards.push_back(card);
            }
        }
    }

    // Method used to shuffle the deck
    void Deck::shuffle() {
        srand(time(nullptr));
        Card temp;
        for (int i = 0; i < cards.size(); i++) {
            // generate random number
            int randNum = rand() % cards.size();

            // rotate cards
            temp = cards[randNum];
            cards[randNum] = cards[i];
            cards[i] = temp;
        }
    }

    // Method used to pull a card from the deck
    Card Deck::draw() {
        Card card = cards.back();
        cards.pop_back();
        return card;
    }
}