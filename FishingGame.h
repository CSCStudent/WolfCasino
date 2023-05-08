//Ethan's Header
#pragma once
#include <iostream>
#include <vector>
#include <Windows.h>
#include "FishingGame/Tile.h"
#include "FishingGame/Anomaly.h"
#include "FishingGame/Fish.h"
#include "Casino.h"

namespace FishingGame {
	class FishingGame : public Casino {
		enum constants { WIDTH = 8, HEIGHT = 8 };
	private:
		Tile ocean[WIDTH][HEIGHT];
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		HANDLE hConsoleInput = GetStdHandle(STD_INPUT_HANDLE);
		std::vector<Fish> tierOne = 
		{
			Fish("Minnow", "A small fish that barely fits on your rod.  We all start somewhere."), 
			Fish("Trout", "As generic as they come."), 
			Fish("Yellowtail", "Not much of the tail is actually yellow."),
			Fish("Crappie", "A name befitting of the quality of this little one.")};
		std::vector<Fish> tierTwo =
		{
			Fish("Sergeant Major", "It won't be barking commands anymore."),
			Fish("Flounder", "Woefully innocent."),
			Fish("Gulper", "For a gulper, this fish has a rather small mouth."),
			Fish("Stonefish", "Not actually made of stone")
		};
		std::vector<Fish> tierThree = {
			Fish("Slurper", "What kind of fish slurps?"),
			Fish("Eel", "You've eelected to catch this fish."),
			Fish("Greater Stonefish", "Actually made of stone."),
			Fish("Bronzefin", "Despite its small size, it hides rows of teeth.")
		};
		std::vector<Fish> tierFour = {
			Fish("Big Gulper", "Capable of draining ponds."),
			Fish("Kidney Stonefish", "Not actually made of kidneys."),
			Fish("Bloodfin", "A bronzefin covered in blood.  Or maybe strawberry jam."),
			Fish("Catfish", "Comes with fur.")
		};
		std::vector<Fish> tierFive = {
			Fish("Nothing", ""),
			Fish("Gulper Eel", "A horrible combination of puns."),
			Fish("Kidneyfish", "May be made of kidneys."),
			Fish("Big Red Fish", "Was once seen off the shores of club penguin.")
		};
		std::vector<Fish> fishCaught;
		int tier = 1;
	public:
		FishingGame();
		~FishingGame();
		static FishingGame* makeGame();
		void run();
		void start();
		void genOcean();
		void refreshOcean();
		void printOcean(int yPos, int xPos);
		void hamlet();
		void playerAction(int& xPos, int& yPos);
		void getFish();
		void almanac();
	};
}