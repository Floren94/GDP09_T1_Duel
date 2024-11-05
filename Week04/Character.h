#pragma once
#include <string>

enum Actions {
	ATTACK,
	PARRY,
	DEFEND
};

class Character {

public:
	Character(int Health, int AttPower, int Defense, std::string Name);

	int GetHealth() const { return Health; }
	int GetAttack() const { return AttPower; }
	int GetDefende() const { return Defense; }
	std::string GetName() const { return Name; }
	void UpdateHealth(int Amount);
	bool IsAlive() const;

	virtual Actions ChooseAction() = 0;

protected:
	int Health;
	int AttPower;
	int Defense;
	std::string Name;
};