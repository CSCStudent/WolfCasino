#pragma once
#ifndef FISH_H
#define FISH_H
#include <iostream>

namespace FishingGame {
	class Fish {
	private: 
		std::string fishName;
		std::string fishDesc;
	public:
		Fish();
		~Fish();
		Fish(std::string name, std::string desc);
		void setDesc(std::string desc);
		void setName(std::string name);
		std::string getName();
		std::string getDesc();
	};
}
#endif