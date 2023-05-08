#pragma once
#include <iostream>
#include "Anomaly.h"

namespace FishingGame {
	Anomaly::Anomaly() {

	}
	Anomaly::~Anomaly() {

	}
	Anomaly::Anomaly(std::string name) {
		this->name = name;
	}
	std::string Anomaly::getName() {
		return name;
	}
	void Anomaly::setName(std::string name) {
		this->name = name;
	}
	int Anomaly::getMovement() {
		return 0;
	}
}