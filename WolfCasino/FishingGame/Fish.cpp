#include <iostream>
#include "Fish.h"

namespace FishingGame {
	Fish::Fish() {
	}
	Fish::~Fish() {
	}
	Fish::Fish(std::string name, std::string desc) {
		this->fishName = name;
		this->fishDesc = desc;
	}
	void Fish::setDesc(std::string desc) {
		this->fishDesc = desc;
	}
	void Fish::setName(std::string name) {
		this->fishName = name;
	}
	std::string Fish::getName() {
		return fishName;
	}
	std::string Fish::getDesc() {
		return fishDesc;
	}
}