#pragma once
#include "Character.h"

class Player : public Character {
	
public:
	Player(int Health, int AttPower, int Defense, std::string Name);

	Actions ChooseAction() override;

};