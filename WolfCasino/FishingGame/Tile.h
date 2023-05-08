#pragma once
#ifndef TILE_H
#define TILE_H
#include <iostream>
#include "Anomaly.h"

namespace FishingGame {
	class Tile {
	private:
		std::string type;
		Anomaly anomaly;
		int numFish;
	public:
		Tile();
		~Tile();
		Tile(std::string type, int numFish);
		Tile(std::string type);
		std::string getType();
		Anomaly getAnomaly();
		int getNumFish();
		void setType(std::string type);
		void setAnomaly(Anomaly anomaly);
		void setNumFish(int numFish);
	};
}

#endif