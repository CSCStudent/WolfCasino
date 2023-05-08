// Carter Lyle
// CSC2034
// 5/07/2023

// Yahtzee
// CSC2034 Spring 2023
// Wolf Casino

#include "player.h"

namespace CSC2034
{



	Player::Player( )
	{

	}

	Player::Player( int paraPlayerNum, int paraGrandTotal )
	{
		playerNum = paraPlayerNum;
		grandTotal = paraGrandTotal;
	}

	Player::Player( int paraPlayerNum )
	{
		playerNum = paraPlayerNum;
	}

	Player::~Player( )
	{

	}

	int Player::getPlayerNum( )
	{
		return playerNum;
	}
	
	int Player::getGrandTotal( )
	{
		return grandTotal;
	}

void Player::addScore( int dice1, int dice2, int dice3, int dice4, int dice5 )//ints are the dice
{
		// Tests for duplicates
	int one = 0;
	int two = 0;
	int three = 0;
	int four = 0;
	int five = 0;
	int six = 0;
	int die[5]{ dice1, dice2, dice3, dice4, dice5 };
	for ( int dice : die )
	{
		if ( dice == 1 )
			one += 1;
		if ( dice == 2 )
			two += 1;
		if ( dice == 3 )
			three += 1;
		if ( dice == 4 )
			four += 1;
		if ( dice == 5 )
			five += 1;
		if ( dice == 6 )
			six += 1;
	}

		// Only matters if yahtzee is 0 or 50
	bool isYahtzee = false;
		// Checks if there is an additional yahtzee
	if ( yahtzee == 50 || yahtzee == 0 )
	{

		if ( one || two || three || four || five || six == 5 )
		{
			isYahtzee = true; // Useful to avoid retesting

				//Applies Yahtzee Bonus
			if ( yahtzee == 50 )
			{
				yahtzeeBonus += 100;
				lowerTotal += 100;
			}
		}
	}

	while ( 1 )
	{
		// If you get a more than one yahtzee, the rest must go into the upper if there is the appropriate slot open
		if ( isYahtzee == true )
		{
			bool exitLoop = false; // To break from while loop if a score is counted from a yahtzee amount the Upper Score
			switch ( dice1 )
			{
			case 1:
				if ( aces == -1 )
				{
					aces = 5;
					upperScore += aces;
					exitLoop = true;
				}
				break;
			case 2:
				if ( twos == -1 )
				{
					twos = 10;
					upperScore += twos;
					exitLoop = true;
				}
				break;
			case 3:
				if ( threes == -1 )
				{
					threes = 15;
					upperScore += threes;
					exitLoop = true;
				}
				break;
			case 4:
				if ( fours == -1 )
				{
					fours = 20;
					upperScore += fours;
					exitLoop = true;
				}
				break;
			case 5:
				if ( fives == -1 )
				{
					fives = 25;
					upperScore += fives;
					exitLoop = true;
				}
				break;
			case 6:
				if ( sixes == -1 )
				{
					sixes = 30;
					upperScore += sixes;
					exitLoop = true;
				}
				break;
			default:
				break;
			}
			if ( exitLoop == true )
				break;
		}

		std::string scorePlacement;
		std::cout << "Where do you want to enter the score in?" << std::endl
			<< "aces, twos, threes, fours, fives, sixes" << std::endl
			<< "threeofakind, fourofakind, fullhouse, smallstraight, largestraigt, yahtzee, or chance" << std::endl;
		std::cin >> scorePlacement;
		std::transform( scorePlacement.begin( ), scorePlacement.end( ), scorePlacement.begin( ), ::tolower );

		if ( aces == -1 && scorePlacement == "aces" )
		{
			aces = one;
			upperScore += aces;
			break;
		}
		else if ( twos == -1 && scorePlacement == "twos" )
		{
			twos = 2 * two;
			upperScore += twos;
			break;
		}
		else if ( threes == -1 && scorePlacement == "threes" )
		{
			threes = 3 * three;
			upperScore += threes;
			break;
		}
		else if ( fours == -1 && scorePlacement == "fours" )
		{
			fours = 4 * four;
			upperScore += fours;
			break;
		}
		else if ( fives == -1 && scorePlacement == "fives" )
		{
			fives = 5 * five;
			upperScore += fives;
			break;
		}
		else if ( sixes == -1 && scorePlacement == "sixes" )
		{
			sixes = 6 * six;
			upperScore += sixes;
			break;
		}
		else if ( threeOfAKind == -1 && scorePlacement == "threeofakind" )
		{
			if ( one || two || three || four || five || six >= 3 )
			{
				threeOfAKind = dice1 + dice2 + dice3 + dice4 + dice5;
				lowerTotal += threeOfAKind;
				break;
			}
			else
			{
				threeOfAKind = 0;
				break;
			}
		}
		else if ( fourOfAKind == -1 && scorePlacement == "fourofakind" )
		{
			if ( one || two || three || four || five || six >= 4 )
			{
				fourOfAKind = dice1 + dice2 + dice3 + dice4 + dice5;
				lowerTotal += fourOfAKind;
				break;
			}
			else
			{
				fourOfAKind = 0;
				break;
			}
		}
		else if ( fullHouse == -1 && scorePlacement == "fullhouse" )
		{
			if ( one || two || three || four || five || six == 3 && one || two || three || four || five || six == 2 )
			{
				fullHouse = 25;
				lowerTotal += fullHouse;
				break;
			}
			else
			{
				fullHouse = 0;
				break;
			}
		}
		else if ( smallStraight == -1 && scorePlacement == "smallstraight" )
		{
			if ( dice1 || dice2 || dice3 || dice4 || dice5 == 3 )
			{
				if ( dice1 || dice2 || dice3 || dice4 || dice5 == 4 )
				{
					if ( dice1 || dice2 || dice3 || dice4 || dice5 == 2 )
					{
						if ( dice1 || dice2 || dice3 || dice4 || dice5 == 1 )
						{
							smallStraight = 30;
							lowerTotal += smallStraight;
							break;
						}
						else if ( dice1 || dice2 || dice3 || dice4 || dice5 == 5 )
						{
							smallStraight = 30;
							lowerTotal += smallStraight;
							break;
						}
					}
					else if ( dice1 || dice2 || dice3 || dice4 || dice5 == 5 )
					{
						if ( dice1 || dice2 || dice3 || dice4 || dice5 == 6 )
						{
							smallStraight = 30;
							lowerTotal += smallStraight;
							break;
						}
					}
				}
			}
		}
		else if ( largeStraight == -1 && scorePlacement == "largestraight" )
		{
			if ( dice1 || dice2 || dice3 || dice4 || dice5 == 2 )
			{
				if ( dice1 || dice2 || dice3 || dice4 || dice5 == 3 )
				{
					if ( dice1 || dice2 || dice3 || dice4 || dice5 == 4 )
					{
						if ( dice1 || dice2 || dice3 || dice4 || dice5 == 5 )
						{
							if ( (dice1 || dice2 || dice3 || dice4 || dice5 == 1) || (dice1 || dice2 || dice3 || dice4 || dice5 == 2) )
							{
								largeStraight = 40;
								lowerTotal += largeStraight;

								break;
							}
						}
					}
				}
			}
			else
			{
				largeStraight = 0;
				break;
			}
		}
		else if ( yahtzee == -1 && scorePlacement == "yahtzee" )
		{
			if ( one || two || three || four || five || six == 5 )
			{
				yahtzee = 50;
				lowerTotal += yahtzee;
				break;
			}
			else
			{
				yahtzee = 0;
				break;
			}

		}
		else if ( chance == -1 && scorePlacement == "chance" )
		{
			chance = dice1 + dice2 + dice3 + dice4 + dice5;
			lowerTotal += chance;
			break;
		}
		else
		{
			// Error caused by an invalid input, such as a mistype
			std::cout << "Error: invalid input" << std::endl;
		}
	}

	//Checks for upperBonus
	if ( upperScore >= 63 )
		upperBonus = 35;

	upperTotal = upperScore + upperBonus;
	grandTotal = upperTotal + lowerTotal;
}

	std::ostream& operator << ( std::ostream&, Player* player )
	{
		return std::cout
			<< "|--------------------|" << std::endl
			<< "|Player " << player->playerNum << " Score Sheet" << std::endl
			<< "|--------------------|" << std::endl
			<< "|   UPPER SECTION    |" << std::endl
			<< "|--------------------|" << std::endl
			<< "| Aces:          " << player->aces << std::endl
			<< "|--------------------|" << std::endl
			<< "| Twos:          " << player->twos << std::endl
			<< "|--------------------|" << std::endl
			<< "| Threes:        " << player->threes << std::endl
			<< "|--------------------|" << std::endl
			<< "| Fours:         " << player->fours << std::endl
			<< "|--------------------|" << std::endl
			<< "| Fives:         " << player->fives << std::endl
			<< "|--------------------|" << std::endl
			<< "| Sixes:         " << player->sixes << std::endl
			<< "|--------------------|" << std::endl
			<< "| Upper Score:   " << player->upperScore << std::endl
			<< "|--------------------|" << std::endl
			<< "| Bonus:         " << player->upperBonus << std::endl
			<< "|--------------------|" << std::endl
			<< "| Upper Total:   " << player->upperTotal << std::endl
			<< "|--------------------|" << std::endl
			<< "|   LOWER SECTION    |" << std::endl
			<< "|--------------------|" << std::endl
			<< "| 3 of a Kind:   " << player->threeOfAKind << std::endl
			<< "|--------------------|" << std::endl
			<< "| 4 of a Kind:   " << player->fourOfAKind << std::endl
			<< "|--------------------|" << std::endl
			<< "| Full House:    " << player->fullHouse << std::endl
			<< "|--------------------|" << std::endl
			<< "| Sm. Straight:  " << player->smallStraight << std::endl
			<< "|--------------------|" << std::endl
			<< "| Lg. Straight:  " << player->largeStraight << std::endl
			<< "|--------------------|" << std::endl
			<< "| YAHTZEE:       " << player->yahtzee << std::endl
			<< "|--------------------|" << std::endl
			<< "| Chance:        " << player->chance << std::endl
			<< "|--------------------|" << std::endl
			<< "| YAHTZEE BONUS: " << player->yahtzeeBonus << std::endl
			<< "|--------------------|" << std::endl
			<< "| Lower Total:   " << player->lowerTotal << std::endl
			<< "|--------------------|" << std::endl
			<< "| Grand Total:   " << player->grandTotal << std::endl
			<< "|--------------------|" << std::endl << std::endl;
	}
}