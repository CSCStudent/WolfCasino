//Ethan's File
#include <iostream>
#include <conio.h>
#include <set>
#include <vector>
#include <cstdlib>
#include <Windows.h>
#include "FishingGame.h"
#include "FishingGame/Tile.h"
#include "FishingGame/Anomaly.h"
#include "FishingGame/Fish.h"

namespace FishingGame {
		enum constants { WIDTH = 8, HEIGHT = 8 };

		FishingGame::FishingGame() {

		}

		FishingGame::~FishingGame() {

		}

		FishingGame* FishingGame::makeGame() {
			return new FishingGame();
		}

		void FishingGame::start() {
			run();
		}

		void FishingGame::run() {
			srand(time(0));
			genOcean();
			refreshOcean();

			int xPos = 3;
			int yPos = 3;
			bool gameOver = false;
			std::cout << "Welcome to fishing game.  The game is about fishing.  Travel the map to fish at fishing spots and collect them all!  Be sure to rest when the fish stop biting." << std::endl;
			printOcean(yPos, xPos);
			playerAction(yPos, xPos);
			while (!gameOver) {
				system("cls");
				printOcean(yPos, xPos);
				playerAction(xPos, yPos);
				if (tier == 6) {
					gameOver = true;
				}
			}
			system("cls");
			std::cout << "You have caught all the fish.  You are become bait, destroyer of oceans.  The fish speak your name in hushed whispers.  No other fisherman will ever compare." << std::endl;
			std::cout << "Press any key to view the fish you've caught.  Exiting the encyclopedia will end the game." << std::endl;
			_getch();
			almanac();
			return;
		}
		void FishingGame::playerAction(int& xPos, int& yPos) {
			SetConsoleTextAttribute(hConsole, 15);
			FlushConsoleInputBuffer(hConsoleInput);
			bool valid = false;
			do {
				std::cout << "Input your next action" << std::endl;
				char playerInput = _getch();
				switch (playerInput) {
				case 'w':
					if (yPos - 1 < 0) {
						std::cout << "You can't move there." << std::endl;
					}
					else if (ocean[yPos - 1][xPos].getType() == "Rock") {
						std::cout << "There's a rock there." << std::endl;
					}
					else {
						yPos = yPos - 1;
						valid = true;
					}
					break;
				case 's':
					if (yPos + 1 >= HEIGHT) {
						std::cout << "You can't move there." << std::endl;
					}
					else if (ocean[yPos + 1][xPos].getType() == "Rock") {
						std::cout << "There's a rock there." << std::endl;
					}
					else {
						yPos = yPos + 1;
						valid = true;
					}
					break;
				case 'a':
					if (xPos - 1 < 0) {
						std::cout << "You can't move there." << std::endl;
					}
					else if (ocean[yPos][xPos - 1].getType() == "Rock") {
						std::cout << "There's a rock there." << std::endl;
					}
					else {
						xPos = xPos - 1;
						valid = true;
					}
					break;
				case 'd':
					if (xPos + 1 >= WIDTH) {
						std::cout << "You can't move there." << std::endl;
					}
					else if (ocean[yPos][xPos + 1].getType() == "Rock") {
						std::cout << "There's a rock there." << std::endl;
					}
					else {
						xPos = xPos + 1;
						valid = true;
					}
					break;
				case 'f':
					valid = true;
					if (yPos == 1 && xPos == 1) {
						hamlet();
					}
					else if (ocean[yPos][xPos].getNumFish() == 0) {
						std::cout << "There are no fish here." << std::endl;
					}
					else {
						getFish();
						ocean[yPos][xPos].setNumFish(ocean[yPos][xPos].getNumFish() - 1);
					}
					break;
				default:
					std::cout << "You can't do that now." << std::endl;
					break;
				}
			} while (!valid);
		}

		void FishingGame::getFish() {
			SetConsoleTextAttribute(hConsole, 15);
			std::cout << "Fishing.";
			Sleep(1000);
			std::cout << ".";
			Sleep(1000);
			std::cout << "." << std::endl;
			std::vector<Fish>* current;
			switch (tier) {
			case 1:
				current = &tierOne;
				break;
			case 2:
				current = &tierTwo;
				break;
			case 3:
				current = &tierThree;
				break;
			case 4:
				current = &tierFour;
				break;
			case 5:
				current = &tierFive;
				break;
			default:
				current = &tierOne;
			}
			if (current->size() != 0) {
				int temp = rand() % current->size();
				fishCaught.push_back(current->at(temp));
				std::cout << "You caught a " << fishCaught.back().getName() << "!" << std::endl;
				current->erase(current->begin() + temp);
				std::cout << "Enter any key to continue..." << std::endl;
				_getch();
			}
			else {
				std::cout << "Nothing's biting...  Maybe try resting?" << std::endl;
				std::cout << "Enter any key to continue..." << std::endl;
				_getch();
			}
		}

		void FishingGame::printOcean(int yPos, int xPos) {
			system("cls");
			//HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, 15); //sets to white
			std::cout << "Use W, A, S, and D to move.  Use F to fish.  Fish at the hamlet to rest." << std::endl;
			for (int i = 0; i < HEIGHT; i++) {
				for (int j = 0; j < WIDTH; j++) {
					if (i == yPos && j == xPos) {
						SetConsoleTextAttribute(hConsole, 23);
						std::cout << " *";
					}
					else if (ocean[i][j].getType() == "Ocean" && ocean[i][j].getNumFish() == 0) {
						SetConsoleTextAttribute(hConsole, 17);
						std::cout << "  ";
					}
					else if (ocean[i][j].getNumFish() > 0) {
						SetConsoleTextAttribute(hConsole, 19);
						std::cout << " O";
					}
					else if (ocean[i][j].getType() == "Rock") {
						SetConsoleTextAttribute(hConsole, 24);
						std::cout << " R";
					}
					else if (ocean[i][j].getType() == "Hamlet") {
						SetConsoleTextAttribute(hConsole, 18);
						std::cout << " H";
					}
					else if (ocean[i][j].getAnomaly().getName() != "None") {
						//todo anomalies must be done
					}
					SetConsoleTextAttribute(hConsole, 15);
				}
				std::cout << std::endl;
			}
		}
		void FishingGame::refreshOcean() {
			switch (tier) {
			case 1:
				if (tierOne.size() == 0) {
					tier = 2;
				}
				break;
			case 2:
				if (tierTwo.size() == 0) {
					tier = 3;
				}
				break;
			case 3:
				if (tierThree.size() == 0) {
					tier = 4;
				}
				break;
			case 4:
				if (tierFour.size() == 0) {
					tier = 5;
				}
			case 5:
				if (tierFive.size() == 0) {
					tier = 6;
				}
			}
			for (int i = 0; i < HEIGHT; i++) {
				for (int j = 0; j < WIDTH; j++) {
					if (ocean[i][j].getNumFish() > 0) {
						ocean[i][j].setNumFish(0);
					}
				}
			}
			int numSpots = rand() % 3 + 2;
			while (numSpots > 0) {
				int yCoord = rand() % HEIGHT;
				int xCoord = rand() % WIDTH;
				if (ocean[yCoord][xCoord].getType() == "Ocean" && ocean[yCoord][xCoord].getNumFish() == 0) {
					ocean[yCoord][xCoord].setNumFish(rand() % 3 + 1);
					numSpots--;
				}

			}
		}

		void FishingGame::hamlet() {
			system("cls");
			SetConsoleTextAttribute(hConsole, 15);
			std::cout << "The hamlet is safe.  If the fish aren't biting, then it's time to take a break." << std::endl;
			std::cout << "Press F to leave, R to rest, or E to view what fish you've caught." << std::endl;
			char playerInput = _getch();
			while (1 == 1) {
				switch (playerInput) {
				case 'f':
					return;
				case 'r':
					std::cout << "You take a break.  The fish are biting again." << std::endl;
					refreshOcean();
					break;
				case 'e':
					almanac();
					break;
				default:
					std::cout << "That's not an action." << std::endl;
					playerInput = _getch();
				}
				std::cout << "Press F to leave, R to rest, or E to view what fish you've caught." << std::endl;
				std::cout << "What do you do now?" << std::endl;
				playerInput = _getch();
			}
		}

		void FishingGame::almanac() {
			while (1 == 1) {
				system("cls");
				std::cout << "Enter a fish's number to read more about it, enter 0 to exit." << std::endl;
				if (fishCaught.empty()) {
					std::cout << "You need to catch some fish first!" << std::endl;
				}
				for (int i = 0; i < fishCaught.size(); i++) {
					std::cout << i + 1 << ". " << fishCaught.at(i).getName() << std::endl;
				}
				bool valid = false;
				char input;
				while (!valid) {
					input = _getch();
					input -= '0';
					if (input == 0) {
						return;
					}
					else if (input < 0 || input > fishCaught.size()) {
						std::cout << "Please enter a valid number." << std::endl;
					}
					else {
						valid = true;
						input--;
					}
				}
				system("cls");
				std::cout << fishCaught.at(input).getName() << std::endl;
				std::cout << fishCaught.at(input).getDesc() << std::endl;
				std::cout << "Press any button to continue.";
				_getch();
			}

		}

		void FishingGame::genOcean() {
			for (int i = 0; i < HEIGHT; i++) {
				int rockSpot = rand() % WIDTH;
				for (int j = 0; j < WIDTH; j++) {
					if (i == 1 && j == 1) {
						ocean[i][j] = Tile("Hamlet", 0);
					}
					else if (i == 2 && j == rockSpot) {
						ocean[i][j] = Tile("Rock", 0);
					}
					else if (i == 4 && j == rockSpot) {
						ocean[i][j] = Tile("Rock", 0);
					}
					else if (i == 6 && j == rockSpot) {
						ocean[i][j] = Tile("Rock", 0);
					}
					else {
						ocean[i][j] = Tile("Ocean", 0);
					}
				}
				//std::cout << i << std::endl;
			}
		}

	}