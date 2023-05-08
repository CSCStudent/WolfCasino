#pragma once
#ifndef ANOMALY_H
#define ANOMALY_H
#include <iostream>

namespace FishingGame {
	class Anomaly {
	private:
		std::string name;
	public:
		Anomaly();
		~Anomaly();
		Anomaly(std::string name);
		std::string getName();
		void setName(std::string name);
		int getMovement();
	};
}

#endif