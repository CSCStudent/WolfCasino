// Carter Lyle
// CSC2034
// 5/07/2023

// Yahtzee
// CSC2034 Spring 2023
// Wolf Casino

#include "yahtzee.h"


namespace CSC2034
{
	Yahtzee::Yahtzee( )
	{
		std::srand( (unsigned int)std::time( nullptr ) );
	}

	Yahtzee::~Yahtzee( )
	{

	}

	Yahtzee* Yahtzee::makeGame( )
	{
		return new Yahtzee;
	}

	void Yahtzee::start( )
	{
		play( );
	}

	void Yahtzee::play( )
	{
		//temp( );
		while ( 1 )
		{
			int numPlayers;
			std::cout << "Enter in the number of player : ";
			std::cin >> numPlayers;
			std::cout << std::endl << std::endl;
			if ( (numPlayers > 0) )
			{
				createPlayers( numPlayers );
				break;
			}
		}

			//calling turns
		for ( int turn = 0; turn < 13; turn++ )
		{
			for ( Player* player : players )
			{
				playerTurn( player );
			}
		}

			// Printing game results
		std::cout << "|---------------------------------------------------------------------------------|" << std::endl
			   	  << "|                                    GAME OVER                                    |" << std::endl
				  << "|---------------------------------------------------------------------------------|" << std::endl << std::endl;
		for ( Player* player : players )
		{
			std::cout << player << std::endl << std::endl;
		}
		
		std::cout << std::endl;

		for ( Player* player : players )
		{
			std::cout << "Player " << player->getPlayerNum( ) << "'s Grand Total: " << player->getGrandTotal( ) << std::endl;
		}
		std::cout << std::endl;
	}

	void Yahtzee::playerTurn( Player* player )
	{
			//Prints player number and score card before their turn
		std::cout << "PLAYER " << player->getPlayerNum( ) << " TURN" << std::endl << std::endl;
		std::cout << player << std::endl << std::endl;

		int rolls = 3;
		roll( dice1 ); roll( dice2 ); roll( dice3 ); roll( dice4 ); roll( dice5 );
		rolls -= 1;
		printDice( );
			
			// catches errors and allows rerolls
		while ( 1 )
		{
			std::string reroll;
			std::cout << "Player" << player->getPlayerNum( ) << ", would you like to REROLL dice or SCORE, ending your turn?" << std::endl << "TYPE: REROLL or SCORE" << std::endl;
			std::cin >> reroll;
			std::transform( reroll.begin( ), reroll.end( ), reroll.begin( ), ::toupper );

			if ( reroll == "REROLL" && rolls != 0 )
			{
				int diceReroll = 1; // Number corresonds with the dice being rerolled
				char rollDice;
				while ( diceReroll < 6 ) // While loop to catch error in input
				{
					switch ( diceReroll )
					{
					case 1:
						std::cout << "Would you like to reroll dice 1?" << std::endl << "Y or N" << std::endl;;
						std::cin >> rollDice;
						rollDice = toupper( rollDice );

						switch ( rollDice )
						{
						case 'Y':
							roll( dice1 );
							diceReroll++;
							break;
						case 'N':
							diceReroll++;
							break;
						default:
							std::cout << "Error: invalid input" << std::endl;
							break;
						}
						break;
					case 2:
						std::cout << "Would you like to reroll dice 2?" << std::endl << "Y or N" << std::endl;;
						std::cin >> rollDice;
						rollDice = toupper( rollDice );

						switch ( rollDice )
						{
						case 'Y':
							roll( dice2 );
							diceReroll++;
							break;
						case 'N':
							diceReroll++;
							break;
						default:
							std::cout << "Error: invalid input" << std::endl;
							break;
						}
						break;
					case 3:
						std::cout << "Would you like to reroll dice 3?" << std::endl << "Y or N" << std::endl;;
						std::cin >> rollDice;
						rollDice = toupper( rollDice );

						switch ( rollDice )
						{
						case 'Y':
							roll( dice3 );
							diceReroll++;
							break;
						case 'N':
							diceReroll++;
							break;
						default:
							std::cout << "Error: invalid input" << std::endl;
							break;
						}
						break;
					case 4:
						std::cout << "Would you like to reroll dice 4?" << std::endl << "Y or N" << std::endl;;
						std::cin >> rollDice;
						rollDice = toupper( rollDice );

						switch ( rollDice )
						{
						case 'Y':
							roll( dice4 );
							diceReroll++;
							break;
						case 'N':
							diceReroll++;
							break;
						default:
							std::cout << "Error: invalid input" << std::endl;
							break;
						}
						break;
					case 5:
						std::cout << "Would you like to reroll dice 5?" << std::endl << "Y or N" << std::endl;;
						std::cin >> rollDice;
						rollDice = toupper( rollDice );

						switch ( rollDice )
						{
						case 'Y':
							roll( dice5 );
							diceReroll++;
							break;
						case 'N':
							diceReroll++;
							break;
						default:
							std::cout << "Error: invalid input" << std::endl;
							break;
						}
						break;
					default:
						break;
					}

				}
				
				printDice( );
				rolls -= 1;
			}
			else if ( reroll == "SCORE" )
			{
				player->addScore( dice1, dice2, dice3, dice4, dice5 );
				break;
			}
			else
			{
					// Error caused by attempting too many rerolls
				if ( reroll == "REROLL" && rolls == 0 )
				{
					std::cout << "Error: no more rolls" << std::endl;
				}
				else
				{
						// Error caused by an invalid input, such as a mistype
					std::cout << "Error: invalid input" << std::endl;
				}
			}
		}
		std::cout << player; //score card
	}
	
		//rolls one dice numbers 1-6
	void Yahtzee::roll( int& dice )
	{
		int low_dist = 1;
		int high_dist = 6;
		
		dice = low_dist + std::rand( ) % (high_dist - low_dist);
	}
	
	void Yahtzee::createPlayers( int numPlayers)
	{
		for ( int i = 0; i < numPlayers; i++ )
		{
			players.push_back( new Player( i + 1 ) );
		}
	}

	void Yahtzee::printDice( )
	{
		std::cout << "|Dice1|Dice2|Dice3|Dice4|Dice5|" << std::endl 
		<< "|  " << dice1 << "  |  " << dice2 << "  |  " << dice3 << "  |  " << dice4 << "  |  " << dice5 << " |" << std::endl;
	}
}
