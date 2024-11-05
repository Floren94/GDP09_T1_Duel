#include "Character.h"

Character::Character(int Health, int AttPower, int Defense, std::string Name) : Health(Health), AttPower(AttPower), Defense(Defense), Name(Name){}

void Character::UpdateHealth(int Amount)
{
	Health += Amount;
}

bool Character::IsAlive() const
{
	return Health > 0;
}

