#include <stdio.h>
#include "Tile.h"
#include "Anomaly.h"

namespace FishingGame {
	Tile::Tile() {
		this->type = "Ocean";
		this->numFish = 0;
	}
	Tile::~Tile() {

	}
	Tile::Tile(std::string type, int numFish) {
		this->type = type;
		this->numFish = numFish;
	}
	Tile::Tile(std::string type) {
		this->type = type;
	}
	std::string Tile::getType() {
		return type;
	}
	Anomaly Tile::getAnomaly() {
		return anomaly;
	}
	int Tile::getNumFish() {
		return numFish;
	}
	void Tile::setType(std::string type) {
		this->type = type;
	}
	void Tile::setAnomaly(Anomaly anomaly) {
		this->anomaly = anomaly;
	}
	void Tile::setNumFish(int numFish) {
		this->numFish = numFish;
	}
}


