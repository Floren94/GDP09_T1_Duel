#include "Enemy.h"

Enemy::Enemy(int Health, int AttPower, int Defense, std::string Name) : Character(Health, AttPower, Defense, Name) , Generator(std::random_device{}()), Distribution(0,2)
{
}

Actions Enemy::ChooseAction()
{
	int Action = Distribution(Generator);

	switch (Action) {
	case 0:
		return ATTACK;
	case 1:
		return PARRY;
	case 2:
		return DEFEND;
	}
}

void Enemy::IncreaseDifficulty(int Round)
{
	Health = 2;
	//std::cout << Round << std::endl;

	switch (Round) {
	case 1:
		return;
	case 2:
		UpdateHealth(Round);
		Name = "Goblin";
		break;
	case 3:
		UpdateHealth(Round);
		AttPower += Round;
		Defense += Round - 2;
		Name = "Warrior";
		break;
	case 4:
		UpdateHealth(Round);
		AttPower += Round;
		Defense += Round - 1;
		Name = "Knight";
		break;
	case 5:
		UpdateHealth(Round);
		AttPower += Round;
		Defense += Round;
		Name = "Lord";
		break;
	}
}
