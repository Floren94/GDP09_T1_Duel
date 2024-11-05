#pragma once
#include "Character.h"
#include <random>
#include <iostream>

class Enemy : public Character {

public:
	Enemy(int Health, int AttPower, int Defense, std::string Name);

	Actions ChooseAction() override;
	void IncreaseDifficulty(int Round);

private:

	std::mt19937 Generator;
	std::uniform_int_distribution<> Distribution;
};
